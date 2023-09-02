#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tokenize.h"

Token *new_token(TokenKind kind, Token *cur, const char *value) {
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->value = strdup(value);
    cur->next = tok;
    return tok;
}

void free_token(Token *tokens) {
    while(tokens != NULL) {
        Token *tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp); 
    }
}

Token *tokenize(const char* input) {
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while(*input) {
        if(isspace(*input)) {
            input++;
            continue;
        }


        if(strncmp(input, "SELECT", SELECT_LENGTH) == 0 && !isalnum(input[SELECT_LENGTH])) {
            cur = new_token(TK_KEYWORD, cur, "SELECT");
            input += SELECT_LENGTH;
            continue;
        }

        if(strncmp(input, "INSERT", INSERT_LENGTH) == 0 && !isalnum(input[INSERT_LENGTH])) {
            cur = new_token(TK_KEYWORD, cur, "INSERT");
            input += INSERT_LENGTH;
            continue;
        }

				if(isalpha(*input)) {
					char identifier[IDENTIFIER_LENGTH];
					int i = 0;
					while(isalnum(*input) || *input == '_' || *input == '@' || *input == '.') {
						identifier[i++] = *input;
						input++;
					}
					identifier[i] = '\0';
					cur = new_token(TK_IDENTIFIER, cur, identifier);
					continue;
				}

				if(isdigit(*input)) {
					char number[NUMBER_LENGTH];
					int j = 0;
					while(isdigit(*input)) {
						number[j++] = *input;
						input++;
					}
					number[j] = '\0';
					cur = new_token(TK_NUM, cur, number);	
					continue;
				}

				cur = new_token(TK_UNKNOWN, cur, input);
        break;
    }

    new_token(TK_EOF, cur, input);
    return head.next;
}
