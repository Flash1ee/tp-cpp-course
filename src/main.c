#include <stdio.h>

#include "grouping.h"
#include "packing.h"
#include "read_write.h"
#include "retcodes.h"


int main() {
    table *data = create_table();
    if (!data) {
        return ALLOC_ERR;
    }
    retcodes rc = fill_table(data, stdin, stdout);
    if (rc != OK) {
        free_table(data);
        return rc;
    }
    table *tb_group = create_table();
    if (!tb_group) {
        free_table(data);
        return ALLOC_ERR;
    }
    rc = group_by_name(data, tb_group);
    if (rc != OK) {
        free_table(data);
        return rc;
    }
    output_data(tb_group, stdout);
    free_table(data);
    free_table(tb_group);

    return rc;
}
