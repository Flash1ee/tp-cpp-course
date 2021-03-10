//
// Created by flashie on 10.03.2021.
//
#include <stdlib.h>
#include "packing.h"
#include <retcodes.h>

table *create_table() {
    table *tb = calloc(1, sizeof(table));
    if (!tb) {
        return NULL;
    }
    return tb;
}

int init_table(table *tb, size_t size) {
    if (!tb) {
        return ARG_ERR;
    }
    tb->list = calloc(size, sizeof(container *));
    if (!tb->list) {
        return ALLOC_ERR;
    }
    tb->capacity = size;
    tb->size = 0;

    return EXIT_SUCCESS;
}

void free_table(table *data) {
    if (!data) {
        return;
    }
    for (int i = 0; i < data->size; i++) {
        free(data->list[i]->type);
        free(data->list[i]);
    }
    free(data->list);
    free(data);
}

container *create_container(char *type, int weight, int capacity) {
    container *value = malloc(sizeof(container));
    if (value) {
        value->type = type;
        value->weight = weight;
        value->max_capacity = capacity;
    }
    return value;
}
