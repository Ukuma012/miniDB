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
		// @todo refactoring

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
			if(strlen(tokens->value) <= COLUMN_USERNAME_SIZE) {
				strncpy(statement->row_to_insert.username, tokens->value, COLUMN_USERNAME_SIZE);
			} else {
				return PREPARE_STRING_TOO_LONG;
			}
		} else {
			return PREPARE_SYNTAX_ERROR;
		}

		tokens = tokens->next;
		if(tokens->kind == TK_IDENTIFIER) {
			if(strlen(tokens->value) <= COLUMN_EMAIL_SIZE) {
				strncpy(statement->row_to_insert.email, tokens->value, COLUMN_EMAIL_SIZE);
			} else {
				return PREPARE_STRING_TOO_LONG;
			}
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
