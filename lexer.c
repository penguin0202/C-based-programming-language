#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "helper.h"
#include "token_info.h"

char *filename = "source.txt";

char *chars;
int chars_len;

char peek() {
    return chars[i];
}

char advance() {
    i++;
}

int i = 0; // index of character to see
int row = 1;
int col = 1;

TOKEN new_token(TOKEN_TYPE type) {
    TOKEN token = {type, NULL, row, col};
    return token;
}

TOKEN new_token(TOKEN_TYPE type, char *value) {
    TOKEN token = {type, value, row, col};
    return token;
}

TOKEN next_token() {
    if (i >= chars_len-1) return new_token(INVALID);
    char c;
    char tc;

    switch (c=chars[i]) {
        case ' ':
            i++;
            col++; 
        case '\n':
            i++;
            row++;
            col = 1;
        case '/': 
            i++;
            col++;
            tc = chars[i];
            if (tc == '/') {
                i++;
                col++;
                while (chars[i] != '\n') {
                    i++;
                }
                i++;
                row++; 
                col = 1;
            }
            else {
                i++;
                col++;
                return new_token(DIV);
            }
        case '+':
            i++;
            col++;
            return new_token(ADD);
    }
}

TOKEN *get_tokens(char *string) {
    int row = 1;
    int col = 1;
    char c = peek();
    char tc;
    while ((c = peek()) != '\0') {
        switch (c) {
            case '+': advance(); tc = peek();
                if (tc == '+') return TOKEN 
        }
    }
}








int main() {
    chars = read_file(filename);
    if (chars == NULL) {
        printf("Not able to open the file.");
        return 1;
    }
    chars_len = strlen(chars);
    


    return 0;
}