#include <stdlib.h>
#include <string.h>
#include "token_info.h"
#include "lexer_helper.h"
#include "dynamic_string.h"
#include "lexer.h"

int advance(LEXER *lexer) {
    if (lexer == NULL) return 0;
    lexer->i++;
    lexer->col++;
    return 1;
}

int advance_line(LEXER *lexer) {
    if (lexer == NULL) return 0;
    lexer->row++;
    lexer->col=1;
    return 1;
}

int store_token_position(LEXER *lexer) {
    if (lexer = NULL) return 0;
    lexer->temp_token_row = lexer->row;
    lexer->temp_token_col = lexer->col;
    return 1;
}

char peek(LEXER *lexer) {
    if (lexer == NULL) return -1;
    return lexer->chars[lexer->i];
}

TOKEN make_token(LEXER *lexer, TOKEN_TYPE type, char *value) {
    return (TOKEN){.type=type, .value=value, .row=lexer->temp_token_row, .col=lexer->temp_token_col};
}

TOKEN next_token(LEXER *lexer) {
    if (lexer->i >= lexer->length) return EOF_TOKEN;

    int temp_row = lexer->row;
    int temp_col = lexer->col;

    /*while (i < chars_len)*/
    char c = peek(lexer);

    #define UNKNOWN_TOKEN (TOKEN){.type=INVALID, .value="", .row=temp_row, .col=temp_col}
    #define PLACEHOLDER_TOKEN (TOKEN){.type=INVALID, .value="", .row=temp_row, .col=temp_col}
    #define EOF_TOKEN (TOKEN){.type=EOF_, .value="", .row=-1, .col=-1}
    #define ERROR_TOKEN (TOKEN){.type=INVALID, .value="", .row=-2, .col=-2}

    if (is_alpha(c)) {
        store_token_position(lexer);
        DYSTR *dystr = dystr_create();
        if (dystr == NULL) {
            printf("creating dynamic string failed");
            return ERROR_TOKEN;
        }

        do {
            dystr_append(dystr, c);
            advance(lexer);
        } while (is_alpha_or_num(c=peek(lexer)));

        char *string = dystr_convert(dystr);
        dystr_free(dystr);
        if (string == NULL) {
            printf("failed to convert dystr into string string");
            return ERROR_TOKEN;
        }
        
        if (strcmp(string, "if") == 0) return make_Token(IF, NULL);
    }

    if (is_num(c)) {
        //parse number
        store_token_position(lexer);
        advance(lexer);
        return PLACEHOLDER_TOKEN;
    }

    if (c == '"') {
        //parse string
        store_token_position(lexer);
        advance(lexer);
        return PLACEHOLDER_TOKEN;
    }

    if (c == '\'') {
        //parse char
        store_token_position(lexer);
        advance(lexer);
        return PLACEHOLDER_TOKEN;
    }

    if (c == ' ') {
        advance(lexer);
        return next_token(lexer);
    }

    if (c == '\n') {
        advance(lexer);
        advance_line(lexer);
        return next_token(lexer);
    }

    if (c == '/') {
        store_token_position(lexer);
        advance(lexer);

        if ((c=peek(lexer)) == '/') {
            do advance(lexer); while (lexer->i < lexer->length && (c=peek(lexer)) != '\n');
            advance(lexer);
            advance_line(lexer);
            return next_token(lexer);
        }

        return make_token_wo(lexer, DIV);
    }

    #define SINGULAR_TOKEN_CHECK(tc, type) \
        if (c == tc) { \
            store_token_position(lexer); \
            advance(lexer); \
            return make(type); \
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
            store_token_position(lexer); \
            advance(lexer); \
            if ((c=peek(lexer)) == tcA) { \
                advance(lexer); \
                return NEW_TOKEN(type2); \
            } \
            return NEW_TOKEN(type1); \
        }
    
    DOUBLE_TOKEN_CHECK('!', NOT, '=', NOT_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('=', ASSIGNER, '=', EQUAL_TO);
    DOUBLE_TOKEN_CHECK('>', GREATER_THAN, '=', GREATER_THAN_OR_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('<', LESS_THAN, '=', LESS_THAN_OR_EQUAL_TO);
    
    return UNKNOWN_TOKEN;
}