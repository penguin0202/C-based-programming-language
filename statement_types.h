typedef enum {
    IF_STATEMENT, 
    IF_ELSE_STATEMENT,
    WHILE_STATEMENT, 
    BREAK_STATEMENT,
    EXPRESSION_STATEMENT,
} STATEMENT_TYPE;

// since they all have to use the same datatype, I've decided: 
// each statement have at most
typedef struct {
    STATEMENT_TYPE type;
    union {
        struct {
            STATEMENT **statement; //block_statement
        } IF_STATEMENT;


        struct {
            STATEMENT **statements;
            size_t length;
        } BLOCK_STATEMENT;







    } value;
} STATEMENT;