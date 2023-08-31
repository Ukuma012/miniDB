#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "tokenize.h"

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer() {
  InputBuffer *input_buffer = calloc(1, sizeof(InputBuffer));
  return input_buffer;
}

void print_prompt() {
  printf("%s", "minidb>> ");
}

void read_input(InputBuffer *input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if(bytes_read <= 0) {
    fprintf(stderr, "error reading input\n");
    exit(1);
  }

  // 末尾の改行を無視
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_bufer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char *argv[])
{
  Token* token;
  InputBuffer *input_buffer = new_input_buffer();
  while(true) {
    print_prompt();
    read_input(input_buffer);

    if(strcmp(input_buffer->buffer, "exit") == 0) {
      close_input_bufer(input_buffer);
      exit(0);
    } else {
      token = tokenize(input_buffer->buffer);
      free_token(token);
    }
  }
  return 0;
}
 