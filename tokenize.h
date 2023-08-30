#ifndef _tokenize.h
#define _tokenize.h

typedef enum {
    TK_COMMAND,
    TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    char *str;
};


#endif