#ifndef IZ2_ARGS_H
#define IZ2_ARGS_H

#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#define SINGLE 0
#define PARALLEL 1

typedef struct {
    size_t streams;
    char *filename;
    bool help;
    bool mode;
} args_t;

args_t *init_args();
args_t *get_args(int argc, char *argv[]);
void free_args(args_t *args);
void print_args(args_t *args, FILE *out);

#endif //IZ2_ARGS_H
