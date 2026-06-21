typedef enum {
    EOF_,
    STRING, // temporary to show that a string of characters exist, not an actual type
    INVALID, 
    IF,
    ELSE,
    WHILE,
    BREAK,
    IDENTIFIER, // can be a custom datatype
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    INT,
    BOOL,
    ASSIGNER, 
    COMMA,
    L_BRACKET,
    R_BRACKET,
    L_PAREN,
    R_PAREN,
    LITERAL_BOOL,
    LITERAL_INT,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN,
    LESS_THAN_OR_EQUAL_TO,
    EQUAL_TO,
    NOT_EQUAL_TO,
    NOT,
    AND,
    OR
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char *value;
    int row;
    int col;
} TOKEN;

void print_token(TOKEN token);