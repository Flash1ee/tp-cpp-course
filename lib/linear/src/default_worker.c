#include <stdio.h>
#include "args.h"
#include "retcodes.h"
#include "data.h"
#include "read_data.h"
#include "worker.h"

retcodes worker(size_t *count, const args_t *args) {
    FILE *f = fopen(args->filename, "r");
    if (!f) {
        return OPEN_ERR;
    }
    records_t *records = create_records();
    if (!records) {
        fclose(f);
        return ALLOC_ERR;
    }
    int rc = read_records(f, records);
    if (rc != OK) {
        free_records(records);
        fclose(f);
        return READ_ERR;
    }
    fclose(f);
    size_t res = 0;
    rc = get_count_nan(records->arr, records->size, &res);
    if (rc) {
        free_records(records);
        return rc;
    }
    *count = res;
    free_records(records);

    return OK;
}
