#ifndef DB_H
#define DB_H

#include "sys/types.h"

typedef enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_COMMAND_INVALID,
} MetaCommandResult;

typedef enum PrepareResult
{
    PREPARE_SUCCESS,
    PREPARE_INVALID_STATEMENT,
} PrepareResult;

typedef enum StateMentType
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StateMentType;

typedef struct InputBuffer
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef struct Statement
{
    StateMentType type;
} Statement;

#endif