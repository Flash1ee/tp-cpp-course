#ifndef TP_CPP_COURSE_DATA_H
#define TP_CPP_COURSE_DATA_H

#include <stdlib.h>
#include "retcodes.h"

typedef struct {
    int id;
    size_t votes;
    union {
        float rating;
        int rating_nan;
    };
} user_record;

#define MIN_RATING 1.0
#define MAX_RATING 5.0

typedef struct {
    user_record **arr;
    size_t count;
    size_t size;
} records_t;

records_t *create_records();
void free_records(records_t *records);
user_record *create_record(int id, float rating, size_t votes);
retcodes init_records(records_t *records, size_t count);
retcodes add_record(records_t *records, user_record *data);

#endif //TP_CPP_COURSE_DATA_H
