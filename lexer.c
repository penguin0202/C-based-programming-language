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

TOKEN new_token(TOKEN_TYPE type) {
    return (TOKEN){.type=type, .value="", .row=temp_row, .col=temp_col};
}

void store_current_token_position() {
    temp_row = row;
    temp_col = col;
}

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

#define UNKNOWN_TOKEN (TOKEN){.type=INVALID, .value="", .row=temp_row, .col=temp_col}

/*#define singular_token_check(c, type) (if (c == '+') { 
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(ADD);
    })*/

TOKEN next_token() {
    if (i >= chars_len-1) return EOF_TOKEN;



    while (i < chars_len) {
        
    }


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
            } while ((c = chars[i]) != '\n');
            advance();
            increment_row_pos();
            reset_col_pos();
            return next_token();
        }

        return new_token(DIV);
    }

    if (c == '+') { 
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(ADD);
    }

    if (c == '-') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(SUB);
    }

    if (c == '*') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(MUL);
    }

    if (c == '%') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(MOD);
    }

    if (c == '{') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(L_BRACKET);
    }

    if (c == '}') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(R_BRACKET);
    }

    if (c == '(') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(L_PAREN);
    }

    if (c == ')') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(R_PAREN);
    }

    if (c == ',') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(COMMA);
    }

    if (c == '&') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(AND);
    }

    if (c == '?') {
        store_current_token_position();
        advance();
        increment_col_pos();
        return new_token(OR);
    }


    case ',': return new_token(COMMA);
    case '&': return new_token(AND);
    case '?': return new_token(OR);
    case '!': 
        if (peek() != '=') return new_token(NOT);
        advance();
        return new_token(NOT_EQUAL_TO);
    case '=': 
        if (peek() != '=') return new_token(ASSIGNER);
        advance();
        return new_token(EQUAL_TO);
    case '>': 
        if (peek() != '=') return new_token(GREATER_THAN);
        advance();
        return new_token(GREATER_THAN_OR_EQUAL_TO);
    case '<': 
        if (peek() != '=') return new_token(LESS_THAN);
        advance();
        return new_token(LESS_THAN_OR_EQUAL_TO);
    default: 
        if (is_alpha(c)) { // not implemented
            advance();
            while (is_alpha(peek())) {
                advance();
            }
            return new_token(STRING);
        }
        else return new_token(INVALID);
    }
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