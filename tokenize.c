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

        if(strncmp(input, "select", SELECT_LENGTH) == 0 && !isalnum(input[SELECT_LENGTH])) {
            cur = new_token(TK_KEYWORD, cur, "select");
            input += SELECT_LENGTH;
            continue;
        }

        if(strncmp(input, "insert", INSERT_LENGTH) == 0 && !isalnum(input[INSERT_LENGTH])) {
            cur = new_token(TK_KEYWORD, cur, "insert");
            input += INSERT_LENGTH;
            continue;
        }

        break;
    }

    new_token(TK_EOF, cur, input);
    return head.next;
}
