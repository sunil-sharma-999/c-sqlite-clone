#ifndef DB_H
#define DB_H

#include "sys/types.h"

typedef struct InputBuffer
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

#endif