#ifndef HW_1_TABLE_UTILS_H
#define HW_1_TABLE_UTILS_H

#include "packing.h"
#include "retcodes.h"

retcodes sort_by_capacity(table *tb_group);
retcodes insert_sort(table *tb);
void free_group(table *tb_group);


#endif //HW_1_TABLE_UTILS_H
