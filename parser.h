#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"

typedef enum
{
		PREPARE_SECCESS,
		PREPARE_SYNTAX_ERROR,
		PREPARE_UNRECOGNIZED_STATEMENT
} ParseResult;

typedef enum
{
		STATEMENT_INSERT,
		STATEMENT_SELECT,
} StatementType;

typedef struct {
		uint32_t id;
		char *username;
		char *email;
} Row;

typedef struct
{
		StatementType type;
		Row row_to_insert;
} Statement;


ParseResult parse_statement_type(Token*, Statement*);
void execute_statement(Statement*);

#endif
