#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "tokenize.h"
#include "parser.h"
#include "table.h"
#include "execute.h"
#include "pager.h"

typedef struct
{
	char *buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer()
{
	InputBuffer *input_buffer = calloc(1, sizeof(InputBuffer));
	return input_buffer;
}

void print_prompt()
{
	printf("%s", "minidb>> ");
}

void read_input(InputBuffer *input_buffer)
{
	ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
	if (bytes_read <= 0)
	{
		fprintf(stderr, "error reading input\n");
		exit(1);
	}

	// 末尾の改行を無視
	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer)
{
	free(input_buffer->buffer);
	free(input_buffer);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Must supply a database filename\n");
		exit(1);
	}

	char* filename = argv[1];

	Token *token;
	Statement statement;
	Table *table;

	InputBuffer *input_buffer = new_input_buffer();
	table = db_open(filename);

	while (true)
	{
		print_prompt();
		read_input(input_buffer);

		if (strcmp(input_buffer->buffer, "exit") == 0)
		{
			close_input_buffer(input_buffer);
			db_close(table);
			printf("%s\n", "bye");
			exit(0);
		}
		else
		{
			token = tokenize(input_buffer->buffer);
			switch (parse_statement_type(token, &statement))
			{
			case (PREPARE_SUCCESS):
				break;
			case (PREPARE_STRING_TOO_LONG):
				printf("%s\n", "String is too long");
				continue;
			case (PREPARE_SYNTAX_ERROR):
				printf("%s\n", "Syntax Error. Could not parse statement.");
				continue;
			case (PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword at start of '%s'.\n", token->value);
				continue;
			}

			switch (execute_statement(&statement, table))
			{
			case (EXECUTE_SUCCESS):
				printf("%s\n", "Executed");
				break;

			case (EXECUTE_FAILED):
				printf("%s\n", "Error execute failed");
				break;

			case (EXECUTE_DUPLICATE_KEY):	
				printf("%s\n", "Error: Duplicate key");
				break;
			}


			free_token(token);
		}
	}
	return 0;
}
