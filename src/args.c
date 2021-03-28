#include <stdlib.h>
#include <string.h>
#include "args.h"

args_t *init_args() {
    args_t *args = calloc(sizeof(args_t), 1);

    return args;
}

void free_args(args_t *args) {
    if (args) {
        free(args->filename);
        free(args);
    }

}

void print_args(args_t *args, FILE *out) {
    if (args) {
        fprintf(out, "help : %d\n", args->help);
        fprintf(out, "filename : %s\n", args->filename);
        fprintf(out, "mode : %d\n", args->mode);
    }
}


args_t *get_args(int argc, char *argv[]) {
    if (argc < 2 || !argv) {
        return NULL;
    }
    args_t *args = init_args();
    if (!args) {
        return NULL;
    }

    const char *short_opt = "hf:o:";
    struct option long_options[] = {
            {"help",     no_argument,       NULL, 'h'},
            {"filename", required_argument, NULL, 'f'},
            {"option",   required_argument, NULL, 'o'},
            {NULL, 0,                       NULL, 0}
    };

    int opt_ind = 0;
    int rez = 0;
    while ((rez = getopt_long(argc, argv, short_opt, long_options, &opt_ind)) != -1) {
        switch (rez) {
            case 'f':
                args->filename = strdup(optarg);
                if (!args->filename) {
                    free_args(args);
                    return NULL;
                }
                break;
            case 'o': {
                int mode = 0;
                if (sscanf(optarg, "%d", &mode) != 1 || (mode != SINGLE && mode != PARALLEL)) {
                    args->help = true;
                }
                args->mode = mode;
                break;
            }
            case ':':
            case 'h':
            case '?':
                args->help = true;
                break;
        }
    }
    if (!args->filename || opt_ind < argc / 2) {
        args->help = true;
    }
    return args;
}
