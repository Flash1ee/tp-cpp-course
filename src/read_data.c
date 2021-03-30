#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include "read_data.h"

retcodes read_size(FILE *f, size_t *size) {
    if (!f) {
        return ARG_ERR;
    }
    char *tmp = NULL;
    size_t count = 0;
    size_t len = 0;
    if (getline(&tmp, &len, f) == -1) {
        free(tmp);
        return READ_ERR;
    }
    tmp[strlen(tmp) - 1] = '\0';
    if (sscanf(tmp, "%zu", &count) != 1) {
        free(tmp);
        return READ_ERR;
    }

    free(tmp);
    *size = count;

    return OK;
}
user_record *read_record(FILE *f) {
    if (!f) {
        return NULL;
    }
    char *tmp = NULL;
    size_t len = 0;
    if (getline(&tmp, &len, f) == -1) {
        free(tmp);
        return NULL;
    }
    tmp[strlen(tmp) - 1] = '\0';
    int id = 0;
    float rating = 0;
    size_t votes = 0;

    if (sscanf(tmp, "%d%zu%f", &id, &votes, &rating) != 3 || id < 0 || rating < 0) {
        free(tmp);
        return NULL;
    }
    free(tmp);
    user_record *record = create_record(id, rating, votes);

    return record;
}
retcodes read_records(FILE *f, records_t *records) {
    if (!f || !records) {
        return ARG_ERR;
    }
    size_t count = 0;
    int rc = read_size(f, &count);
    if (rc != OK) {
        return rc;
    }

    rc = init_records(records, count);
    if (rc != OK) {
        free(records);
        return ALLOC_ERR;
    }
    for (size_t i = 0; i < count; ++i) {
        user_record *record = read_record(f);
        if (!record) {
            free_records(records);
            return ALLOC_ERR;
        }
        rc = add_record(records, record);
        if (rc != OK) {
            free_records(records);
            free(record);
            return ALLOC_ERR;
        }
    }
    return rc;
}