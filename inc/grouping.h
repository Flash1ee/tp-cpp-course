#ifndef HW_1_GROUPING_H
#define HW_1_GROUPING_H

#include "packing.h"

int group_by_type(table *data, table *tb_group);
int sort_by_capacity(table *tb_group);
int cmp(const void *a, const void *b);
int not_tb_group(table *tb_group, char *type);
void free_group(table *tb_group);

#endif //HW_1_GROUPING_H
