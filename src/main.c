//
// Created by flashie on 06.03.2021.
//
#include <stdlib.h>
#include "packing.h"
#include "retcodes.h"
#include "input.h"
#include "grouping.h"

int main() {
    table *data = create_table();
    if (!data) {
        return ALLOC_ERR;
    }
    int rc = fill_table(data);
    if (rc) {
        free_table(data);
        return rc;
    }
    table *tb_group = create_table();
    if (!tb_group) {
        free_table(data);
        return ALLOC_ERR;
    }
    rc = group_by_type(data, tb_group);
    if (rc) {
        free_table(data);
        return rc;
    }
    output_data(tb_group);
    free_table(data);
    free_table(tb_group);

    return rc;
}
