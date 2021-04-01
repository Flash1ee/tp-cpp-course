#ifndef TP_CPP_COURSE_RETCODES_H
#define TP_CPP_COURSE_RETCODES_H

typedef enum {
    OK,
    ARG_ERR,
    READ_ERR,
    ALLOC_ERR,
    OPEN_ERR,
    FORK_ERR,
    WAITPID_ERR,
} retcodes;

#endif //TP_CPP_COURSE_RETCODES_H
