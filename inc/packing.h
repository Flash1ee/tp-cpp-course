//
// Created by flashie on 06.03.2021.
//

#ifndef HW_1_PACKING_H
#define HW_1_PACKING_H

typedef struct {
    char *type;
    int weight;
    int max_capacity;
} container;

typedef struct {
    container **list;
    size_t size;
    size_t capacity;
} table;

#endif //HW_1_PACKING_H
