#ifndef HW_1_READ_WRITE_H
#define HW_1_READ_WRITE_H

#include "packing.h"
#include "retcodes.h"

retcodes fill_table(table *data, FILE *stream_in, FILE *stream_out);

retcodes read_count_records(FILE *stream_in, FILE *stream_out, size_t *count);

void output_data(table *data, FILE *stream);

retcodes fill_container(container **dest, FILE *stream_in, FILE *stream_out);

void print_container(container *unit, FILE *stream);


#endif //HW_1_READ_WRITE_H
