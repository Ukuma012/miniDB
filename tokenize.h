#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdint.h>

#define IDENTIFIER_LENGTH 100
#define NUMBER_LENGTH 255
#define SELECT_LENGTH 6
#define INSERT_LENGTH 6

typedef enum {
	TK_KEYWORD,
	TK_IDENTIFIER,
	TK_NUM,
	TK_UNKNOWN,
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
