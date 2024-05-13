#define _GNU_SOURCE
#include "main.h"
#include "stdlib.h"
#include "stdio.h"
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

int main()
{
    InputBuffer *input_buffer = new_input_buffer();
    while (1)
    {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0)
        {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Invalid command '%s'.\n", input_buffer->buffer);
        }
    }
}