#ifndef TOKENIZE_H
#define TOKENIZE_H

#define SELECT_LENGTH 6
#define INSERT_LENGTH 6

typedef enum {
    TK_KEYWORD,
    TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    char *value;
};
Token *tokenize(const char*);
void free_token(Token* );

#endif