#include "statement_types.h"
#include "parser.h"
#include "token_info.h"
#include <stdlib.h>
#include "expression_types.h"

void print_parser_error(TOKEN got_token, TOKEN expected_token, char message[]) {
    printf();
}

PARSER *parser_create() {
    PARSER *parser = malloc(sizeof(PARSER));
    if (parser == NULL) return NULL; //error?
    parser->tokens = NULL;
    parser->i = 0;
    parser->length=0;
    return parser;
}

int parser_tokens_append(PARSER *parser, TOKEN token) {
    if (parser->length == 0) {
        parser->length = 1;
        parser->tokens = malloc(sizeof(TOKEN));
    }
    else {
        parser->length++;
        TOKEN *new_tokens = realloc(parser->tokens, sizeof(TOKEN) * parser->length);
        if (new_tokens == NULL) return 0; //failed
        parser->tokens = new_tokens;
    }
    parser->tokens[parser->length-1] = token;
    return 1; //success
}

void parser_tokens_print(PARSER *parser) {
    if (parser->tokens != NULL){
        for (int i = 0; i < parser->length; i++) {
            print_token(parser->tokens[i]);
        }
    }
}

void advance(PARSER *parser) {
    parser->i++;
}

TOKEN peek(PARSER *parser) {
    return parser->tokens[parser->i];
}

STATEMENT *next_statement(PARSER *parser) {
    //if (parser->i >= parser->length) return EMPTY/EOF/STATEMENT

    TOKEN token = peek(parser);
    STATEMENT *statement = malloc(sizeof(STATEMENT));
    if (token.type==KEYWORD_IF) {
        advance(parser);
        EXPRESSION *condition = parse_expression(parser);
        token = peek(parser);
        if (token.type != L_BRACKET) {
            
        }






        statement->value.IF_STATEMENT.statement;
    }
}

EXPRESSION *parse_atom() {

}

EXPRESSION *parse_expression(PARSER *parser) {
    EXPRESSION *expression = malloc(sizeof(EXPRESSION));

    return expression;
}