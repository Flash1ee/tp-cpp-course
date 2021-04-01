#ifndef IZ2_PARALLEL_WORKER_H
#define IZ2_PARALLEL_WORKER_H

#include <stdlib.h>
#include "retcodes.h"
#include "args.h"
#include "data.h"

typedef retcodes (*worker)(size_t *count, const args_t *args);

retcodes parallel_worker(size_t *count, const args_t *args);
retcodes parallel_count_nan(user_record **shared_memory, size_t len, pid_t *processes, long cnt_processes);

#endif //IZ2_PARALLEL_WORKER_H
