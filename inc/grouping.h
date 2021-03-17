#ifndef HW_1_GROUPING_H
#define HW_1_GROUPING_H

#include "packing.h"
#include "retcodes.h"


retcodes group_by_name(table *data, table *tb_group);

int not_tb_group(table *tb_group, char *type);

#endif //HW_1_GROUPING_H
