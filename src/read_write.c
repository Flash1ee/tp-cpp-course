#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"
#include "packing.h"
#include "retcodes.h"

#define ERROR_GETLINE -1
#define MIN_LEN 2

retcodes read_count_records(FILE *stream_in, FILE *stream_out, size_t *count) {
    if (!stream_in || !stream_out || !count) {
        return ARG_ERR;
    }
    int num = 0;
    fprintf(stream_out, "Input count of records: ");
    if (fscanf(stream_in, "%d%*c", &num) != 1 || num < 0) {
        return INPUT_ERR;
    }
    *count = (size_t) num;

    return OK;

}

retcodes fill_table(table *data, FILE *stream_in, FILE *stream_out) {
    if (!data || !stream_in || !stream_out) {
        return ARG_ERR;
    }
    size_t count = 0;
    retcodes rc = read_count_records(stream_in, stream_out, &count);
    if (rc != OK) {
        return rc;
    }

    rc = init_table(data, count);
    if (rc != OK) {
        return ALLOC_ERR;
    }

    for (size_t i = 0; i < count; ++i) {
        rc = fill_container(data->list + i, stream_in, stream_out);
        if (rc != OK) {
            break;
        }
        data->size++;
    }
    if (rc != OK) {
        free_table(data);
        return ALLOC_ERR;
    }


    return OK;
}

retcodes fill_container(container **dest_ptr, FILE *stream_in, FILE *stream_out) {
    if (!dest_ptr || !stream_in || !stream_out) {
        return ARG_ERR;
    }

    size_t len = 0;
    char *tmp = NULL;
    int weight = 0;
    int capacity = 0;

    fprintf(stream_out, "Input type of container(string): ");
    if (getline(&tmp, &len, stream_in) == ERROR_GETLINE || strlen(tmp) < MIN_LEN) {
        free(tmp);
        return INPUT_ERR;
    }
    tmp[strlen(tmp) - 1] = '\0';
    fprintf(stream_out, "Input weight of container: ");
    if (fscanf(stream_in, "%d%*c", &weight) != 1 || weight < 0) {
        free(tmp);
        return INPUT_ERR;
    }
    fprintf(stream_out, "Input max_capacity of container: ");
    if (fscanf(stream_in, "%d%*c", &capacity) != 1 || capacity < 0) {
        free(tmp);
        return INPUT_ERR;
    }
    *dest_ptr = create_container(tmp, weight, capacity);
    if (!(*dest_ptr)) {
        free(tmp);
        return ALLOC_ERR;
    }

    return OK;
}

void output_data(table *data, FILE *stream) {
    if (!data || !stream) {
        return;
    }
    for (size_t i = 0; i < data->size; ++i) {
        print_container(data->list[i], stream);
    }
}

void print_container(container *unit, FILE *stream) {
    if (!unit || !stream) {
        return;
    }
    if (unit->type) {
        fprintf(stream, "Type of container is %s\n", unit->type);
    }
    fprintf(stream, "Weight: %zu\n", unit->weight);
    fprintf(stream, "Max_capacity: %zu\n", unit->max_capacity);
    fprintf(stream, "\n");
}

