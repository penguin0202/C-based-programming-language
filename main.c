#include "lexer.h"
#include "helpers/files_helper.h"
#include <string.h>
#include "token_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

char filename[] = "source.txt";

int main() {
    char *file = read_file(filename);
    if (file == NULL) {
        printf("Error reading file: %s\n", filename);
        return 1;
    }
    LEXER *lexer = lexer_create(file);
    free(file);

    

    PARSER *parser = parser_create();
    if (parser == NULL) {
        printf("somehow allocating parser struct failed");
        return 1;
    }

    TOKEN token;
    while ((token = next_token(lexer)).type != EOF_ && token.type != DEV_ERROR) {
        parser_tokens_append(parser, token);

        if (token.value != NULL) {
            free(token.value);
        }
    }

    parser_tokens_print(parser);

    free(lexer->chars);
    free(lexer);

    return 0;
}