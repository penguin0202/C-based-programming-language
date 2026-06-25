#include "token_info.h"
#include <stddef.h>

#ifndef LEXER_H
#define LEXER_H

typedef struct {
    char *chars;
    size_t length;
    int i;
    int row;
    int col;
    int temp_token_row; // temp
    int temp_token_col; // temp
} LEXER;

#endif

TOKEN next_token(LEXER *lexer);
LEXER *lexer_create(char *chars);