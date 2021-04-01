#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <wait.h>
#include "worker.h"
#include "read_data.h"

static void process_terminate(size_t cnt_processes, pid_t *const processes) {
    for (size_t i = 0; i < cnt_processes; ++i) {
        kill(processes[i], SIGKILL);
    }

    while (cnt_processes != 0) {
        pid_t waited_pid = waitpid(0, NULL, WUNTRACED);

        if (waited_pid < 0) {
            break;
        }

        if (waited_pid) {
            cnt_processes--;
        }
    }
}

static int exit_processes(size_t cnt_process, pid_t *const processes) {
    if (!processes) {
        return ARG_ERR;
    }
    int status = 0;
    while (cnt_process != 0) {
        for (size_t i = 0; i < cnt_process; i++) {
            pid_t waited_pid = waitpid(0, &status, WUNTRACED);

            if (waited_pid < 0) {
                return WAITPID_ERR;
            }
            if (waited_pid) {
                if (WIFEXITED(status)) {
                    cnt_process--;
                } else if (WIFSIGNALED(status) || WIFSTOPPED(status)) {
                    return WAITPID_ERR;
                }
            }
        }
    }
    return OK;
}

static retcodes parallel_count_nan(user_record **shared_memory, size_t len, pid_t *processes, long cnt_processes) {
    if (!shared_memory || !processes || cnt_processes < 1) {
        return ARG_ERR;
    }

    size_t offset = (len - 1) / cnt_processes + (len - 1) % cnt_processes;
    pid_t child = 0;

    user_record **shared_offset = shared_memory + 1;
    len--;

    for (long i = 0; i < cnt_processes; ++i) {
        child = fork();
        if (child == -1) {
            process_terminate(i, processes);
            return FORK_ERR;
        } else if (child != 0) {
            processes[i] = child;

            shared_offset += offset;
            len -= offset;

            if (len < offset) {
                offset = len;
            }
        } else {
            size_t count = 0;
            retcodes rc = get_count_nan(shared_offset, offset, &(count));
            if (rc != OK) {
                process_terminate(i, processes);
                exit(rc);
            }
            *(_Atomic size_t *) shared_memory += count;
            exit(EXIT_SUCCESS);
        }

    }
    return OK;
}

retcodes worker(size_t *count, const args_t *args) {
    if (!count || !args || !args->filename || args->mode != PARALLEL) {
        return ARG_ERR;
    }
    long cnt_processes = sysconf(_SC_NPROCESSORS_ONLN);
    if (args->streams) {
        cnt_processes = args->streams;
    }
    FILE *f = fopen(args->filename, "r");
    if (!f) {
        return OPEN_ERR;
    }
    records_t *records = create_records();
    if (!records) {
        fclose(f);
        return ALLOC_ERR;
    }
    retcodes rc = read_records(f, records);
    if (rc != OK) {
        free_records(records);
        fclose(f);
        return READ_ERR;
    }
    fclose(f);
    // Отображение массива структур в "общую" память
    user_record **shared_memory = mmap(NULL, sizeof(user_record *) * (records->count + 1), PROT_READ | PROT_WRITE,
                                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!shared_memory) {
        free_records(records);
        return ALLOC_ERR;
    }
    memcpy(shared_memory + 1, records->arr, records->count * sizeof(user_record *));
    size_t shared_len = records->count + 1;
    shared_memory[0] = 0;


    pid_t *processes = calloc(cnt_processes, sizeof(pid_t));
    if (!processes) {
        free_records(records);
        munmap(shared_memory, sizeof(user_record *) * (shared_len + 1));
        return ALLOC_ERR;
    }
    rc = parallel_count_nan(shared_memory, shared_len, processes, cnt_processes);
    if (rc != OK) {
        free_records(records);
        munmap(shared_memory, sizeof(user_record *) * (shared_len + 1));
        process_terminate(cnt_processes, processes);
        free(processes);
        return rc;
    }
    rc = exit_processes(cnt_processes, processes);
    *count = (_Atomic size_t) shared_memory[0];

    munmap(shared_memory, sizeof(user_record *) * (shared_len + 1));

    free(processes);
    free_records(records);

    return rc;
}
