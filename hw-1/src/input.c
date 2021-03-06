//
// Created by flashie on 06.03.2021.
//
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "packing.h"
#include "retcodes.h"

int input_data(table *data) {
    if (!data) {
        return ARG_ERR;
    }
    fprintf(stdout, "Input count of records: ");
    int count = 0;
    if (fscanf(stdin, "%d", &count) != 1 || count < 1) {
        return INPUT_ERR;
    }
    clean_buf();
    data->list = calloc(count, sizeof(container *));
    if (!data->list) {
        return ALLOC_ERR;
    }
    size_t len = 0;
    char *tmp = NULL;
    int weight = 0;
    int capacity = 0;

    for (int i = 0; i < count; i++) {
        fprintf(stdout, "Input type of container(string): ");
        if (getline(&tmp, &len, stdin) == -1 || strlen(tmp) < 2) {
            free(tmp);
            free_list(data);
            return INPUT_ERR;
        }
        tmp[strlen(tmp) - 1] = '\0';
        fprintf(stdout, "Input weight of container: ");
        if (fscanf(stdin, "%d", &weight) != 1) {
            free(tmp);
            free_list(data);
            return INPUT_ERR;
        }
        clean_buf();
        fprintf(stdout, "Input max_capacity of container: ");
        if (fscanf(stdin, "%d", &capacity) != 1) {
            free(tmp);
            free_list(data);
            return INPUT_ERR;
        }
        clean_buf();
        data->list[i] = calloc(1, sizeof(container));
        if (!data->list[i]) {
            free(tmp);
            free_list(data);
            return ALLOC_ERR;
        }
        data->list[i]->type = tmp;
        data->list[i]->weight = weight;
        data->list[i]->max_capacity = capacity;

        tmp = NULL;
        len = 0;
    }
    data->size = count;
    data->capacity = count;
    fprintf(stdout, "Successful input data\n");
    return EXIT_SUCCESS;
}

void output_data(table *data) {
    if (!data) {
        return;
    }
    for (int i = 0; i < data->size; i++) {
        fprintf(stdout, "Record %d\n", i);
        fprintf(stdout, "Type of container is %s\n", data->list[i]->type);
        fprintf(stdout, "Weight: %d\n", data->list[i]->weight);
        fprintf(stdout, "Max_capacity: %d\n", data->list[i]->max_capacity);
    }
}

void free_list(table *data) {
    if (!data) {
        return;
    }
    for (int i = 0; i < data->capacity; i++) {
        free(data->list[i]->type);
        free(data->list[i]);
    }
}

void clean_buf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
