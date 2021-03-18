#include <stdlib.h>
#include "table_utils.h"

retcodes sort_by_capacity(table *tb_group) {
    if (!tb_group) {
        return ARG_ERR;
    }
    retcodes rc = insert_sort(tb_group);

    return rc;
}

void free_group(table *data) {
    if (!data) {
        return;
    }
    for (size_t i = 0; i < data->size; ++i) {
        free(data->list[i]->type);
        free(data->list[i]);
    }
}

retcodes insert_sort(table *tb) {
    if (!tb) {
        return ARG_ERR;
    }
    container *new = NULL;
    int pos = 0;

    for (size_t i = 1; i < tb->size; ++i) {
        new = tb->list[i];
        pos = i - 1;
        while (pos >= 0 && tb->list[pos]->max_capacity > new->max_capacity) {
            tb->list[pos + 1] = tb->list[pos];
            pos = pos - 1;
        }
        tb->list[pos + 1] = new;
    }

    return OK;
}
