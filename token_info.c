#include "token_info.h"
#include <stdio.h>

char *token_types[] = {
    "DEV_ERROR",
    "DEV_PLACEHOLDER",
    "EOF_",
    "LITERAL_STRING", // temporary to show that a string of characters exist, not an actual type
    "UNKNOWN", 
    "KEYWORD_IF",
    "KEYWORD_ELSE",
    "KEYWORD_WHILE",
    "KEYWORD_BREAK",
    "IDENTIFIER", // can be a custom datatype
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "DATATYPE_INT",
    "DATATYPE_BOOL",
    "ASSIGNER", 
    "COMMA",
    "L_BRACKET",
    "R_BRACKET",
    "L_PAREN",
    "R_PAREN",
    "LITERAL_BOOL",
    "LITERAL_INT",
    "GREATER_THAN",
    "GREATER_THAN_OR_EQUAL_TO",
    "LESS_THAN",
    "LESS_THAN_OR_EQUAL_TO",
    "EQUAL_TO",
    "NOT_EQUAL_TO",
    "NOT",
    "AND",
    "OR"
};

void print_token(TOKEN token) {
    printf("%s| ", token_types[token.type]);
    if (token.value != NULL) {
        printf("%s; ", token.value);
    }
    else {
        printf("NULL; ");
    }
    printf("row=%d, col=%d\n", token.row, token.col);
}