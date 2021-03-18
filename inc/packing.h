#ifndef HW_1_PACKING_H
#define HW_1_PACKING_H

#include "retcodes.h"

typedef struct {
    char *type;
    size_t weight;
    size_t max_capacity;
} container;

typedef struct {
    container **list;
    size_t size;
    size_t capacity;
} table;

table *create_table();

retcodes init_table(table *tb, size_t capacity);

void free_table(table *data);

container *create_container(char *type, int weight, int capacity);

void free_container(container *source);

#endif //HW_1_PACKING_H
