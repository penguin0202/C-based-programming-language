#include <stdlib.h>
#include <stdio.h>
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
        case ' ': i++; col++; c=chars[i];
        case '\n': i++; row++; col = 1; c=chars[i];
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
                break;
            }
            else { i++; col++; return new_token(DIV); }
        case '+': i++; col++; return new_token(ADD);
        case '-': i++; col++; return new_token(SUB);
        case '*': i++; col++; return new_token(MUL);
        case '%': i++; col++; return new_token(MOD);
        case '{': i++; col++; return new_token(L_BRACKET);
        case '}': i++; col++; return new_token(R_BRACKET);
    }
}

int main() {
    chars = read_file(filename);
    if (chars == NULL) {
        printf("Not able to open the file.");
        return 1;
    } chars_len = strlen(chars);

    return 0;
}