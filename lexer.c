#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char *filename = "source.txt";

char *chars;
int i = 0; // index of character to see

char *read_file(char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    //need +1 because it has to end with null terminator \0
    char *string = malloc(sizeof(char) * (length+1));

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}

typedef enum {
    KEYWORD,
    IDENTIFIER, // can be a custom datatype
    OPERATOR,
    DEFAULT_DATATYPE, // right now: int, bool
    ASSIGNER,
    DELIMITER,
    LITERAL_BOOL,
    LITERAL_INT,
    OTHER
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char *value; 
} TOKEN;

char peek() {
    return chars[i];
}

char advance() {
    i++;
}

TOKEN *get_tokens(char *string) {
    char c;
    char tc;
    while ((c = peek()) != '\0') {
        switch (c) {
            case '+': advance(); tc = peek();
                if (tc == '+') return 
        }
    }
}



int main() {
    chars = read_file(filename);
    if (chars == NULL) {
        printf("Not able to open the file.");
        return 1;
    }
    


    return 0;
}