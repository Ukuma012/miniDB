#include <stdio.h>
#include <stdbool.h>
#include "tokenize.h"

Token *token;

bool consume(char op) {
    if (token->kind != TK_COMMAND || token->str[0] != op) {
        return false;
    }
    token = token->next;
    return true;
}