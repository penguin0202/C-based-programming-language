#include <stdio.h>
#include <stdlib.h>

char *read_file(char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    //need +1 because it has to end with null terminator \0
    char *file_contents = malloc(length+1);

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        file_contents[i] = c;
        i++;
    }
    file_contents[i] = '\0';

    fclose(file);

    return file_contents;
}