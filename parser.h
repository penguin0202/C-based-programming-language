#include "token_info.h"
#include "statement_types.h"

typedef struct {
    TOKEN *tokens;
    int i;
    size_t length;
} PARSER;

PARSER *parser_create();
int parser_tokens_append(PARSER *parser, TOKEN token);
void parser_tokens_print(PARSER *parser);
void advance(PARSER *parser);
TOKEN peek(PARSER *parser);
STATEMENT *next_statement(PARSER *parser);