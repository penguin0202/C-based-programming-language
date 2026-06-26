typedef enum {
    
} EXPRESSION_TYPE;

typedef struct {
    EXPRESSION_TYPE type;
    union {
        struct {

        } BinaryExpression;
        
        struct {

        } LiteralIntExpression;
    } value;
} EXPRESSION;