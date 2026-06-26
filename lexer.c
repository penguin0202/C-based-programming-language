#include <stdlib.h>
#include <string.h>
#include "token_info.h"
#include "helpers/dynamic_string.h"
#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

int is_alpha(char c) {
    return strchr("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL;
}

int is_num(char c) {
    return strchr("0123456789", c) != NULL;
}

int is_alpha_or_num(char c) {
    return is_alpha(c) || is_num(c);
}

LEXER *lexer_create(char *chars) {
    LEXER *lexer = malloc(sizeof(LEXER));

    char *chars_copy = malloc(strlen(chars) + 1);
    if (chars_copy == NULL) {
        printf("failed to malloc a copy of chars");
        return NULL;
    }
    strcpy(chars_copy, chars);
    lexer->chars = chars_copy;
    lexer->length = strlen(lexer->chars);
    lexer->i = 0;
    lexer->row = 1;
    lexer->col = 1;
    lexer->temp_token_row = 1;
    lexer->temp_token_col = 1;
}

void advance(LEXER *lexer) {
    lexer->i++;
    lexer->col++;
}

void advance_line(LEXER *lexer) {
    lexer->row++;
    lexer->col=1;
}

void store_token_position(LEXER *lexer) {
    lexer->temp_token_row = lexer->row;
    lexer->temp_token_col = lexer->col;
}

char peek(LEXER *lexer) {
    return lexer->chars[lexer->i];
}

TOKEN make_token(LEXER *lexer, TOKEN_TYPE type, char *value) {
    return (TOKEN){.type=type, .value=value, .row=lexer->temp_token_row, .col=lexer->temp_token_col};
}

TOKEN determine_named_token(LEXER *lexer, char *string) {
    if (strcmp(string, "if") == 0) return make_token(lexer, KEYWORD_IF, NULL);
    if (strcmp(string, "else") == 0) return make_token(lexer, KEYWORD_ELSE, NULL);
    if (strcmp(string, "while") == 0) return make_token(lexer, KEYWORD_WHILE, NULL);
    if (strcmp(string, "break") == 0) return make_token(lexer, KEYWORD_BREAK, NULL);
    if (strcmp(string, "int") == 0) return make_token(lexer, DATATYPE_INT, NULL);
    if (strcmp(string, "bool") == 0) return make_token(lexer, DATATYPE_BOOL, NULL);

    // I created string_copy because I want to pass string into make_token, but I
    // am going to free it after I return from this function; a copy is needed
    char *string_copy = malloc(strlen(string) + 1);
    if (string_copy == NULL) {
        printf("failed to malloc a copy of string");
        return make_token(lexer, DEV_ERROR, "failed to malloc a copy of string");
    }
    strcpy(string_copy, string);
    return make_token(lexer, IDENTIFIER, string_copy);
}

TOKEN next_token(LEXER *lexer) {
    if (lexer->i >= lexer->length) return make_token(lexer, EOF_, NULL);

    char c;

    while (lexer->i < lexer->length) {
        c = peek(lexer);

        if (c == ' ') {
            advance(lexer);
            continue;
        }

        if (c == '\n') {
            advance(lexer);
            advance_line(lexer);
            continue;
        }

        if (c == '/') {
            store_token_position(lexer);
            advance(lexer);

            if ((c=peek(lexer)) == '/') {
                do advance(lexer); while (lexer->i < lexer->length && (c=peek(lexer)) != '\n');
                advance(lexer);
                advance_line(lexer);
                continue;
            }

            return make_token(lexer, DIV, NULL);
        }

        break;
    }

    if (is_alpha(c)) {
        store_token_position(lexer);
        DYSTR *dystr = dystr_create();
        if (dystr == NULL) {
            printf("creating dynamic string failed");
            return make_token(lexer, DEV_ERROR, "creating dynamic string failed");
        }

        do {
            dystr_append(dystr, c);
            advance(lexer);
        } while (is_alpha_or_num(c=peek(lexer)));

        char *string = dystr_convert(dystr);
        dystr_free(dystr);
        if (string == NULL) {
            printf("failed to convert dystr into string string");
            return make_token(lexer, DEV_ERROR, "failed to convert dystr into string string");
        }
        TOKEN named_token = determine_named_token(lexer, string);
        free(string);
        return named_token;
    }

    if (is_num(c)) {
        //parse number
        store_token_position(lexer);
        DYSTR *dystr = dystr_create();
        if (dystr == NULL) {
            printf("creating dynamic string failed");
            return make_token(lexer, DEV_ERROR, "creating dynamic string failed");
        }

        do {
            dystr_append(dystr, c);
            advance(lexer);
        } while (is_num(c=peek(lexer)));

        char *string = dystr_convert(dystr);
        dystr_free(dystr);
        if (string == NULL) {
            printf("failed to convert dystr into string string");
            return make_token(lexer, DEV_ERROR, "failed to convert dystr into string string");
        }
        char *string_copy = malloc(strlen(string) + 1);
        if (string_copy == NULL) {
            printf("failed to malloc a copy of string");
            return make_token(lexer, DEV_ERROR, "failed to malloc a copy of string");
        }
        strcpy(string_copy, string);
        free(string);
        return make_token(lexer, LITERAL_INT, string_copy);
    }

    #define SINGULAR_TOKEN_CHECK(tc, type) \
        if (c == tc) { \
            store_token_position(lexer); \
            advance(lexer); \
            return make_token(lexer, type, NULL); \
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
                return make_token(lexer, type2, NULL); \
            } \
            return make_token(lexer, type1, NULL); \
        }
    
    DOUBLE_TOKEN_CHECK('!', NOT, '=', NOT_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('=', ASSIGNER, '=', EQUAL_TO);
    DOUBLE_TOKEN_CHECK('>', GREATER_THAN, '=', GREATER_THAN_OR_EQUAL_TO);
    DOUBLE_TOKEN_CHECK('<', LESS_THAN, '=', LESS_THAN_OR_EQUAL_TO);
    
    return make_token(lexer, UNKNOWN, NULL);
}