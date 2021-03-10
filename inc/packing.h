//
// Created by flashie on 06.03.2021.
//

#ifndef HW_1_PACKING_H
#define HW_1_PACKING_H

typedef struct {
    char *type;
    int weight;
    int max_capacity;
} container;

typedef struct {
    container **list;
    size_t size;
    size_t capacity;
} table;

table *create_table();

int init_table(table *tb, size_t size);

void free_table(table *data);

container *create_container(char *type, int weight, int capacity);

void free_container(container *source);

#endif //HW_1_PACKING_H
