typedef struct Lexer {
    char *chars;
    size_t length;
    int i;
    int row;
    int col;
    int temp_token_row; // temp
    int temp_token_col; // temp
} LEXER;