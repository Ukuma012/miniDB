#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef enum
{
		PREPARE_SUCCESS,
		PREPARE_STRING_TOO_LONG,
		PREPARE_SYNTAX_ERROR,
		PREPARE_UNRECOGNIZED_STATEMENT
} ParseResult;

typedef enum
{
		STATEMENT_BTREE,
		STATEMENT_CONST,
		STATEMENT_INSERT,
		STATEMENT_SELECT,
} StatementType;

typedef struct {
	uint32_t id;
	char username[COLUMN_USERNAME_SIZE + 1];
	char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct
{
		StatementType type;
		Row row_to_insert;
} Statement;

ParseResult parse_statement_type(Token*, Statement*);

#endif
