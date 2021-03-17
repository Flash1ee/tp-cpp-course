#include <stdlib.h>
#include "packing.h"
#include "retcodes.h"
#include "read_write.h"
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
    rc = group_by_name(data, tb_group);
    if (rc) {
        free_table(data);
        return rc;
    }
    output_data(tb_group);
    free_table(data);
    free_table(tb_group);

    return rc;
}
