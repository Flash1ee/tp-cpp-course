//
// Created by flashie on 06.03.2021.
//
#include <stdlib.h>
#include "packing.h"
#include "input.h"
#include "grouping.h"
int main() {
    table data = {};
    table tb_group = {};
    int rc = input_data(&data);
    if (rc) {
        free_list(&data);
        return rc;
    }
    rc = group_by_type(&data, &tb_group);
    if (rc) {
        free_list(&data);
        free_list(&tb_group);
        return rc;
    }
    output_data(&tb_group);
    free_list(&data);
    free_group(&tb_group);
    return rc;
}
