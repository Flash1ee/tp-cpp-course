#ifndef IZ2_WORKER_H
#define IZ2_WORKER_H

#include <stdlib.h>
#include "retcodes.h"
#include "args.h"
#include "data.h"

typedef retcodes (*worker_t)(size_t *count, const args_t *args);

retcodes worker(size_t *count, const args_t *args);

#endif //IZ2_WORKER_H
