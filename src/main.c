#include <stdio.h>
#include <stdlib.h>
#include "retcodes.h"
#include "args.h"
#include "../lib/linear/inc/default_worker.h"
#include "../lib/parallel//inc/parallel_worker.h"


/*
 * --help / -h - необязательно
 *  -d - директория с файлом для считывания
 *  -f - имя файла
 * -default - один процесс - статическая библиотека
 * -parallel - несколько процессов - динамическая библиотека
 */
void show_help(FILE *out) {
    fprintf(out,"Программа запускается следующим образом\n"
           "./main.out [args]\n"
           "Возможные аргументы:\n"
           "--help (-h) Вывод подсказки(необязательный параметр)\n"
           "--directory [path] (-d) указание пути до директории с обрабатываемым файлом(обязательный параметр)\n"
           "--filename [name] (-f) имя файла (обязательный)\n"
           "--option [mode] (-o) режим запуска: 0 - singleprocessing, 1 - multiprocessing (обязательный)\n");
}


typedef retcodes (*worker)(size_t *count, const args_t *args);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return ARG_ERR;
    }
    args_t *args = get_args(argc, argv);
    if (!args) {
        return ARG_ERR;
    }
    if (args->help) {
        show_help(stdout);
        free_args(args);
        return EXIT_SUCCESS;
    }
    size_t res = 0;
    worker worker_used = NULL;
    if (args->mode == SINGLE) {
        worker_used = default_worker;
    } else {
        worker_used = parallel_worker;
    }
    int rc = worker_used(&res, args);
    if (rc) {
        free_args(args);
        return rc;
    }

    printf("COUNT NAN RATING %zu\n", res);
    free_args(args);

    return OK;
}
