#ifndef TOKEN_INFO_H
#define TOKEN_INFO_H
#include <stddef.h>

typedef enum {
    DEV_ERROR,
    DEV_PLACEHOLDER,
    EOF_,
    UNKNOWN, 

    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,
    KEYWORD_BREAK,

    DATATYPE_INT,
    DATATYPE_BOOL,

    LITERAL_BOOL,
    LITERAL_INT,
    LITERAL_STRING, // temporary to show that a string of characters exist, not an actual type


    
    
    
    
    
    IDENTIFIER, // can be a custom datatype
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    
    ASSIGNER, 
    COMMA,
    L_BRACKET,
    R_BRACKET,
    L_PAREN,
    R_PAREN,
    
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN,
    LESS_THAN_OR_EQUAL_TO,
    EQUAL_TO,
    NOT_EQUAL_TO,
    NOT,
    AND,
    OR
} TOKEN_TYPE;

extern char *token_types[];

typedef struct {
    TOKEN_TYPE type;
    char *value;
    int row;
    int col;
} TOKEN;

#endif

void print_token(TOKEN token);