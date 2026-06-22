#include "lexer.h"
#include "files_helper.h"
#include <string.h>
#include "token_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

char *filename = "source.txt";

int main() {
    char *file = read_file(filename);
    if (file == NULL) {
        printf("Error reading file: %s\n", filename);
        return 1;
    }
    LEXER *lexer = malloc(sizeof(LEXER));
    lexer->chars = file;
    lexer->length = strlen(lexer->chars);
    lexer->i = 0;
    lexer->row = 1;
    lexer->col = 1;
    lexer->temp_token_row = 1;
    lexer->temp_token_col = 1;

    TOKEN token;
    while ((token = next_token(lexer)).type != EOF_ && token.type != DEV_ERROR) {
        print_token(token);
    }

    free(lexer->chars);
    free(lexer);
    return 0;
}