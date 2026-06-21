#include "token_info.h"

void print_token(TOKEN token) {
    printf("%d; row=%d, col=%d\n", token.type, token.row, token.col);
}