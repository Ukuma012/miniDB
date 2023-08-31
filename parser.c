#include <stdio.h>
#include <string.h>
#include "parser.h"

ParseResult parse_statement_type(Token* tokens, Statement* statement) {
    if(tokens->kind == TK_KEYWORD && strcmp(tokens->value, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SECCESS;
    }

    if(tokens->kind == TK_KEYWORD && strcmp(tokens->value, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SECCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
    
}

void execute_statement(Statement* statment) {
    switch (statment->type) {
        case (STATEMENT_INSERT):
            printf("%s", "This is where we would do an insert.\n");
            break;

        case (STATEMENT_SELECT):
            printf("%s", "This is where we would do a select.\n");
            break;
    }
}