#include <string.h>

int is_alpha(char c) {
    return strchr("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL;
}

int is_num(char c) {
    return strchr("0123456789", c) != NULL;
}

int is_alpha_or_num(char c) {
    return is_alpha(c) || is_num(c);
}