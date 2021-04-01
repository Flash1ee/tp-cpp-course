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

args_t *get_args(int argc, char *argv[]) {
    if (argc < 2 || !argv) {
        return NULL;
    }
    args_t *args = init_args();
    if (!args) {
        return NULL;
    }

    const char *short_opt = "hf:o:s:";
    struct option long_options[] = {
            {"help",     no_argument,       NULL, 'h'},
            {"filename", required_argument, NULL, 'f'},
            {"option",   required_argument, NULL, 'o'},
            {"streams",  required_argument, NULL, 's'},
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
            case 's': {
                size_t cnt_streams = 0;
                if (sscanf(optarg, "%zu", &cnt_streams) != 1 || (cnt_streams < 1)) {
                    args->help = true;
                }
                args->streams = cnt_streams;
                break;
            }
            case ':':
            case 'h':
            case '?':
                args->help = true;
                break;
        }
    }
    if (!args->filename || optind < argc) {
        args->help = true;
    }
    return args;
}
