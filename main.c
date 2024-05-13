#define _GNU_SOURCE
#include "main.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void print_prompt() { printf("db > "); }

void close_input_buffer(InputBuffer *buf)
{
    free(buf->buffer);
    free(buf);
}

void read_input(InputBuffer *buf)
{
    ssize_t bytes_read =
        getline(&(buf->buffer), &(buf->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    buf->input_length = bytes_read - 1;
    buf->buffer[bytes_read - 1] = '\0';
}

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

MetaCommandResult do_meta_command(InputBuffer *buf)
{
    if (strcmp(buf->buffer, ".exit") == 0)
    {
        close_input_buffer(buf);
        exit(EXIT_SUCCESS);
        return META_COMMAND_SUCCESS;
    }
    else
    {
        return META_COMMAND_INVALID;
    }
}

PrepareResult prepare_statement(InputBuffer *buf, Statement *stmt)
{
    if (strncmp(buf->buffer, "insert", 6) == 0)
    {
        stmt->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(buf->buffer, "select") == 0)
    {
        stmt->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_INVALID_STATEMENT;
}

void execute_statement(Statement *stmt)
{
    switch (stmt->type)
    {
    case STATEMENT_INSERT:
        printf("Insert statement");
        break;
    case STATEMENT_SELECT:
        printf("Select statement");
        break;
    default:
        break;
    }
}

int main()
{
    InputBuffer *input_buffer = new_input_buffer();
    while (1)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer))
            {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_INVALID):
                printf("Invalid command '%s'\n", input_buffer->buffer);
                continue;
            }
        }
        // Statements
        Statement stmt;
        switch (prepare_statement(input_buffer, &stmt))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_INVALID_STATEMENT):
            printf("Invalid keyword at start of '%s'.\n",
                   input_buffer->buffer);
            continue;
        }

        execute_statement(&stmt);
        printf(" Executed.\n");
    }
}