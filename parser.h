#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"

typedef enum
{
    PREPARE_SECCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} ParseResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

ParseResult parse_statement_type(Token*, Statement*);
void execute_statement(Statement*);

#endif