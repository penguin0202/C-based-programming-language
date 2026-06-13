#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "files_helper.h"
#include "token_info.h"
#include "lexer_helper.h"

char *filename = "source.txt";

char *chars;
int chars_len;

char c;

int i = 0; // index of character to see
int row = 1;
int col = 1;

char peek() {
    return chars[i];
}

/*TOKEN new_token(TOKEN_TYPE type) {
    TOKEN token = {type, NULL, row, col};
    return token;
}*/





void advance() {
    i++;
}

void increment_col_pos() {
    col++;
}

void reset_col_pos() {
    col = 1;
}

void increment_row_pos() {
    row++;
}



/*
TOKEN new_token(TOKEN_TYPE type, char *value) {
    TOKEN token = {type, value, row, col};
    return token;
}*/

int temp_row = 1;
int temp_col = 1;

void store_current_token_position() {
    temp_row = row;
    temp_col = col;
}

TOKEN new_token(TOKEN_TYPE type) {
    return (TOKEN){.type=type, .value="", .row=temp_row, .col=temp_col};
}

#define UNKNOWN_TOKEN (TOKEN){.type=INVALID, .value="", .row=temp_row, .col=temp_col}

TOKEN next_token() {
    if (i >= chars_len-1) return EOF_TOKEN;
    /*while (i < chars_len)*/
    char c = chars[i];

    if (is_alpha(c)) {
        //parse string
        return PLACEHOLDER_TOKEN;
    }

    if (is_num(c)) {
        //parse number
        return PLACEHOLDER_TOKEN;
    }

    if (c == ' ') {
        advance();
        increment_col_pos();
        return next_token();
    }

    if (c == '\n') {
        advance();
        increment_row_pos();
        reset_col_pos();
        return next_token();
    }

    if (c == '/') {
        store_current_token_position();
        advance();
        increment_col_pos();
        c = chars[i];

        if (c == '/') {
            do {
                advance();
                increment_col_pos();
            } while ((c=chars[i]) != '\n');
            advance();
            increment_row_pos();
            reset_col_pos();
            return next_token();
        }

        return new_token(DIV);
    }

    #define SINGULAR_TOKEN_CHECK(tc, type) \
        if (c == tc) { \
            store_current_token_position(); \
            advance(); \
            increment_col_pos(); \
            return new_token(type); \
        }

    SINGULAR_TOKEN_CHECK('+', ADD);
    SINGULAR_TOKEN_CHECK('-', SUB);
    SINGULAR_TOKEN_CHECK('*', MUL);
    SINGULAR_TOKEN_CHECK('%', MOD);
    SINGULAR_TOKEN_CHECK('{', L_BRACKET);
    SINGULAR_TOKEN_CHECK('}', R_BRACKET);
    SINGULAR_TOKEN_CHECK('(', L_PAREN);
    SINGULAR_TOKEN_CHECK(')', R_PAREN);
    SINGULAR_TOKEN_CHECK(',', COMMA);
    SINGULAR_TOKEN_CHECK('&', AND);
    SINGULAR_TOKEN_CHECK('?', OR);

    #define DOUBLE_TOKEN_CHECK(tc, type1, tcA, type2) \
        if (c == tc) { \
            store_current_token_position(); \
            advance(); \
            increment_col_pos(); \
            if ((c=chars[i]) == tcA) { \
                advance(); \
                increment_col_pos(); \
                return new_token(type2); \
            } \
            return new_token(type1); \
        }
    
    DOUBLE_TOKEN_CHECK('!', NOT, '=', NOT_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('=', ASSIGNER, '=', EQUAL_TO);
    DOUBLE_TOKEN_CHECK('>', GREATER_THAN, '=', GREATER_THAN_OR_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('<', LESS_THAN, '=', LESS_THAN_OR_EQUAL_TO);
    
    return UNKNOWN_TOKEN;
}

void print_token(TOKEN token) {
    printf("%d; row=%d, col=%d\n", token.type, token.row, token.col);
}

int main() {
    chars = read_file(filename);
    if (chars == NULL) {
        printf("Not able to open the file.");
        return 1;
    } chars_len = strlen(chars);

    TOKEN token;
    while ((token = next_token()).type != INVALID) {
        print_token(token);
    }

    return 0;
}