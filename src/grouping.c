//
// Created by flashie on 06.03.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grouping.h"
#include "retcodes.h"

int group_by_type(table *data, table *tb_group) {
    if (!data || !tb_group || !data->size) {
        return ARG_ERR;
    }
    int rc = init_table(tb_group, data->size);
    if (rc) {
        return ALLOC_ERR;
    }
    int pos = 0;
    for (int i = 0; i < data->size; i++) {
        pos = not_tb_group(tb_group, data->list[i]->type);
        if (pos == -1) {
            char *str = strdup(data->list[i]->type);
            if (!str) {
                free_table(tb_group);
                return ALLOC_ERR;
            }

            tb_group->list[tb_group->size] = create_container(str, data->list[i]->weight, data->list[i]->max_capacity);
            if (!tb_group->list[tb_group->size]) {
                free_group(tb_group);
                free(str);
                return ALLOC_ERR;
            }
            tb_group->size++;
        } else {
            tb_group->list[pos]->weight += data->list[i]->weight;
            tb_group->list[pos]->max_capacity += data->list[i]->max_capacity;
        }
    }
    if (data->size != tb_group->size) {
        rc = sort_by_capacity(tb_group);
        if (rc) {
            free_table(tb_group);
        }
    }

    return rc;
}

int cmp(const void *a, const void *b) {
    const container *first = a;
    const container *sec = b;

    return first->max_capacity > sec->max_capacity;
}

int sort_by_capacity(table *tb_group) {
    if (!tb_group) {
        return ARG_ERR;
    }
    qsort(tb_group->list, tb_group->size, sizeof(container *), cmp);
    return EXIT_SUCCESS;
}

static int not_tb_group(table *tb_group, char *type) {
    for (int i = 0; i < tb_group->size; i++) {
        if (!strcmp(tb_group->list[i]->type, type)) {
            return i;
        }
    }
    return -1;
}

void free_group(table *data) {
    for (int i = 0; i < data->size; i++) {
        free(data->list[i]->type);
        free(data->list[i]);
    }
}