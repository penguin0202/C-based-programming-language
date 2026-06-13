#include <stdbool.h>
#include <string.h>

bool contains(char *string, char c) {
    int len = strlen(string);
    int i = 0;
    while (i < len) {
        if (c == string[i]) return true;
        i++;
    } return false;
}

bool is_alpha(char c) {
    return contains("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", c);
}

bool is_num(char c) {
    return contains("0123456789", c);
}

bool is_alpha_or_num(char c) {
    return is_alpha(c) || is_num(c);
}