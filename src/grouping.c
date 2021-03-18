#include <stdlib.h>
#include <string.h>
#include "grouping.h"
#include "table_utils.h"

#define NOT_FOUND -1

retcodes add_group_record(table *tb_group, container *data) {
    char *str = strdup(data->type);
    if (!str) {
        free_table(tb_group);
        return ALLOC_ERR;
    }
    tb_group->list[tb_group->size] = create_container(str, data->weight, data->max_capacity);
    if (!tb_group->list[tb_group->size]) {
        free_group(tb_group);
        free(str);
        return ALLOC_ERR;
    }
    tb_group->size++;

    return OK;
}

retcodes group_by_name(table *data, table *tb_group) {
    if (!data || !tb_group || !data->size) {
        return ARG_ERR;
    }
    retcodes rc = init_table(tb_group, data->size);
    if (rc != OK) {
        return ALLOC_ERR;
    }
    for (size_t i = 0; i < data->size; ++i) {
        int pos = get_pos_group(tb_group, data->list[i]->type);
        if (pos == NOT_FOUND) {
            rc = add_group_record(tb_group, data->list[i]);
            if (rc != OK) {
                return rc;
            }
        } else {
            tb_group->list[pos]->weight += data->list[i]->weight;
            tb_group->list[pos]->max_capacity += data->list[i]->max_capacity;
        }
    }
    if (data->size != tb_group->size) {
        rc = sort_by_capacity(tb_group);
        if (rc != OK) {
            free_table(tb_group);
        }
    }

    return rc;
}

int get_pos_group(table *tb_group, char *type) {
    for (size_t i = 0; i < tb_group->size; ++i) {
        if (!strcmp(tb_group->list[i]->type, type)) {
            return i;
        }
    }
    return NOT_FOUND;
}
