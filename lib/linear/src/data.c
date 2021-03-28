#include <assert.h>
#include "data.h"

records_t *create_records() {
    records_t *records = calloc(1, sizeof(records_t));

    return records;
}
void free_records(records_t *records) {
    if (records) {
        for (size_t i = 0; i < records->count; ++i) {
            free(records->arr[i]);
        }
        free(records->arr);
        free(records);
    }
}
retcodes init_records(records_t *records, size_t count) {
    if (!records || !count) {
        return ARG_ERR;
    }
    records->arr = calloc(count, sizeof(user_record *));
    if (!records->arr) {
        return ALLOC_ERR;
    }
    records->size = count;
    records->count = 0;

    return OK;
}

retcodes add_record(records_t *records, user_record *data) {
    if (!records || !data) {
        return ARG_ERR;
    }
    assert(records->count < records->size);

    records->arr[records->count] = data;
    records->count++;

    return OK;
}

user_record *create_record(int id, float rating, size_t votes) {
    user_record *record = calloc(1, sizeof(user_record));
    if (record) {
        record->id = id;
        record->votes = votes;
        if (rating < MIN_RATING) {
            record->rating_nan = NAN;
        } else {
            record->rating = rating;
        }
    }

    return record;
}
retcodes get_count_nan(records_t *records, size_t *count) {
    if (!records || !records->arr || !count) {
        return ARG_ERR;
    }
    size_t tmp_count = 0;

    for (size_t i = 0; i < records->count; ++i) {
        if (!records->arr[i]) {
            return ARG_ERR;
        }
        if (records->arr[i]->rating == NAN) {
            tmp_count++;
        }
    }
    *count = tmp_count;

    return OK;
}
