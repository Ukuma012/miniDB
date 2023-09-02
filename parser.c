#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

ParseResult parse_statement_type(Token* tokens, Statement* statement) {
		if(tokens->kind == TK_UNKNOWN) {
			return PREPARE_UNRECOGNIZED_STATEMENT;
		}

    if(tokens->kind == TK_KEYWORD && strcmp(tokens->value, "SELECT") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SECCESS;
    }

		// INSERT 
		// INSERT 1 Ukuma ukuma@gmail.com
    if(tokens->kind == TK_KEYWORD && strcmp(tokens->value, "INSERT") == 0) {
        statement->type = STATEMENT_INSERT;

				tokens = tokens->next;
				if(tokens->kind == TK_NUM) {
					uint32_t num;
					num = strtol(tokens->value, NULL, 10);
					statement->row_to_insert.id = num;
				} else {
					return PREPARE_SYNTAX_ERROR;
				}

				tokens = tokens->next;
				if(tokens->kind == TK_IDENTIFIER) {
					statement->row_to_insert.username = strdup(tokens->value);
				} else {
					return PREPARE_SYNTAX_ERROR;
				}

				tokens = tokens->next;
				if(tokens->kind == TK_IDENTIFIER) {
					statement->row_to_insert.email = strdup(tokens->value);
				} else {
					return PREPARE_SYNTAX_ERROR;
				}

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
