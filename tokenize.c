#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "tokenize.h"

Token *token;

bool consume(char op) {
    if (token->kind != TK_STRING || token->str[0] != op) {
        return false;
    }
    token = token->next;
    return true;
}

bool at_eof() {
    return token->kind == TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str) {
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}

Token *tokenize(char *p) {
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while(*p) {
        if(isspace(*p)) {
            p++;
            continue;
        }
    }
}