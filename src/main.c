#include <stdio.h>
#include <stdlib.h>
#include "read_data.h"
#include "retcodes.h"
#include "args.h"

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
        return EXIT_FAILURE;
    }
    FILE *f = fopen(args->filename, "r");
    if (!f) {
        free_args(args);
        return ARG_ERR;
    }
    records_t *records = create_records();
    if (!records) {
        free_args(args);
        fclose(f);
    }
    int rc = read_records(f, records);
    if (rc != OK) {
        free_records(records);
        free_args(args);
        fclose(f);
        return READ_ERR;
    }
    fclose(f);
    print_args(args, stdout);
    free_args(args);
    free_records(records);


    return 0;
}
