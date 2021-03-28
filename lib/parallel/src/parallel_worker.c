#include "../inc/parallel_worker.h"

retcodes parallel_worker(size_t *count, const args_t *args) {
    if (!count || !args) {
        return ARG_ERR;
    }
    return OK;
}