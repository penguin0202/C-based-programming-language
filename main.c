#include "lexer.h"
#include "files_helper.h"
#include <string.h>
#include "token_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

char filename[] = "source.txt";

int main() {
    char *file = read_file(filename);
    if (file == NULL) {
        printf("Error reading file: %s\n", filename);
        return 1;
    }
    LEXER *lexer = lexer_create(file);
    free(file);
    TOKEN token;
    while ((token = next_token(lexer)).type != EOF_ && token.type != DEV_ERROR) {
        print_token(token);
        if (token.value != NULL) {
            free(token.value);
        }
    }

    free(lexer->chars);
    free(lexer);
    return 0;
}