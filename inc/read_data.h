#ifndef IZ2_READ_DATA_H
#define IZ2_READ_DATA_H

#include <stdio.h>
#include "data.h"
#include "retcodes.h"


retcodes read_records(FILE *f, records_t *records);
user_record *read_record(FILE *f);
retcodes read_size(FILE *f, size_t *size);

#endif //IZ2_READ_DATA_H
