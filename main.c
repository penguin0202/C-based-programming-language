#include "lexer.h"
#include "files_helper.h"
#include <string.h>

char *filename = "source.txt";

int main() {
    char *file = read_file(filename);
    LEXER lexer = (LEXER){file, strlen(file), 0, 1, 1};
    


    TOKEN token;
    while ((token = next_token()).type != EOF_) {
        print_token(token);
    }
    return 0;

    



}