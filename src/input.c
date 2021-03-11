#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "packing.h"
#include "retcodes.h"

int fill_table(table *data) {
    if (!data) {
        return ARG_ERR;
    }
    int count = 0;
    fprintf(stdout, "Input count of records: ");
    if (fscanf(stdin, "%d", &count) != 1 || count < 1) {
        return INPUT_ERR;
    }
    clean_buf();
    int rc = EXIT_SUCCESS;

    rc = init_table(data, count);
    if (rc) {
        return ALLOC_ERR;
    }
    for (int i = 0; i < count; i++) {
        rc = fill_container(data->list + i);
        if (rc) {
            free_table(data);
            return ALLOC_ERR;
        }
        data->size++;
    }
    fprintf(stdout, "Successful input data\n");

    return EXIT_SUCCESS;
}

int fill_container(container **dest_ptr) {
    if (!dest_ptr) {
        return ARG_ERR;
    }

    size_t len = 0;
    char *tmp = NULL;
    int weight = 0;
    int capacity = 0;

    fprintf(stdout, "Input type of container(string): ");
    if (getline(&tmp, &len, stdin) == -1 || strlen(tmp) < 2) {
        free(tmp);
        return INPUT_ERR;
    }
    tmp[strlen(tmp) - 1] = '\0';
    fprintf(stdout, "Input weight of container: ");
    if (fscanf(stdin, "%d", &weight) != 1) {
        free(tmp);
        return INPUT_ERR;
    }
    clean_buf();
    fprintf(stdout, "Input max_capacity of container: ");
    if (fscanf(stdin, "%d", &capacity) != 1) {
        free(tmp);
        return INPUT_ERR;
    }
    clean_buf();
    *dest_ptr = create_container(tmp, weight, capacity);
    if (!(*dest_ptr)) {
        free(tmp);
        return ALLOC_ERR;
    }

    return EXIT_SUCCESS;
}

void output_data(table *data) {
    if (!data) {
        return;
    }
    for (size_t i = 0; i < data->size; i++) {
        fprintf(stdout, "Record %zu\n", i);
        fprintf(stdout, "Type of container is %s\n", data->list[i]->type);
        fprintf(stdout, "Weight: %d\n", data->list[i]->weight);
        fprintf(stdout, "Max_capacity: %d\n", data->list[i]->max_capacity);
    }
}

void clean_buf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
