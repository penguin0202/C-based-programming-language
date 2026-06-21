#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "files_helper.h"
#include "token_info.h"
#include "lexer_helper.h"
#include "dynamic_string.h"

char *filename = "source.txt";

char *chars;
int chars_len;



int i = 0; // index of character to see
int row = 1;
int col = 1;

char peek() {
    return chars[i];
}

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
#define PLACEHOLDER_TOKEN (TOKEN){.type=INVALID, .value="", .row=temp_row, .col=temp_col}
#define EOF_TOKEN (TOKEN){.type=EOF_, .value="", .row=-1, .col=-1}
#define ERROR_TOKEN (TOKEN){.type=INVALID, .value="", .row=-2, .col=-2}

TOKEN next_token() {
    if (i >= chars_len) return EOF_TOKEN;

    /*while (i < chars_len)*/
    char c = peek();

    if (is_alpha(c)) {
        store_current_token_position();
        i++;
        col++;
        DYSTR *dystr = dystr_create();
        if (dystr == NULL) {
            printf("creating dynamic string failed");
            return ERROR_TOKEN;
        }
        dystr_append(dystr, c);
        while(is_alpha_or_num(c=peek())) {
            dystr_append(dystr, c);
            i++;
            col++;
        }
        return PLACEHOLDER_TOKEN;
    }

    if (is_num(c)) {
        //parse number
        store_current_token_position();
        i++;
        col++;
        return PLACEHOLDER_TOKEN;
    }

    if (c == '"') {
        //parse string
        i++;
        col++;
        return PLACEHOLDER_TOKEN;
    }

    if (c == '\'') {
        //parse char
        i++;
        col++;
        return PLACEHOLDER_TOKEN;
    }

    if (c == ' ') {
        i++;
        col++;
        return next_token();
    }

    if (c == '\n') {
        i++;
        row++;
        col=1;
        return next_token();
    }

    if (c == '/') {
        store_current_token_position();
        i++;
        col++;

        if ((c=peek()) == '/') {
            do {
                i++;
                col++;
            } while (i < chars_len && (c=peek()) != '\n');
            i++;
            row++;
            col=1;
            return next_token();
        }

        return new_token(DIV);
    }

    #define SINGULAR_TOKEN_CHECK(tc, type) \
        if (c == tc) { \
            store_current_token_position(); \
            i++; \
            col++; \
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
            i++; \
            col++; \
            if ((c=peek()) == tcA) { \
                i++; \
                col++; \
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

int main() {
    if ((chars=read_file(filename)) == NULL) {
        printf("Not able to open the file.");
        return 1;
    } chars_len = strlen(chars);

    TOKEN token;
    while ((token = next_token()).type != EOF_) {
        print_token(token);
    }
    return 0;
}