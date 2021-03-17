#include <stdlib.h>
#include "table_utils.h"

retcodes sort_by_capacity(table *tb_group) {
    if (!tb_group) {
        return ARG_ERR;
    }
    insert_sort(tb_group);

    return OK;
}

void free_group(table *data) {
    for (size_t i = 0; i < data->size; i++) {
        free(data->list[i]->type);
        free(data->list[i]);
    }
}

void insert_sort(table *tb) {
    container *new = 0;
    int pos = 0;

    for (size_t i = 1; i < tb->size; i++) {
        new = tb->list[i];
        pos = (int) i - 1;
        while (pos >= 0 && tb->list[pos]->max_capacity > new->max_capacity) {
            tb->list[pos + 1] = tb->list[pos];
            pos = pos - 1;
        }
        tb->list[pos + 1] = new;
    }
}
