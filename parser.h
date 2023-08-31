#ifndef PARSER_H
#define PARSER_H

#include "tokenize.h"

typedef enum
{
    PREPARE_SECCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

PrepareResult parse_statement_type(Token*, Statement*);
void execute_statement(Statement*);

#endif