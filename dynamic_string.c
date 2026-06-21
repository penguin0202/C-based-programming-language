#include <stdlib.h>
#include "dynamic_string.h"

DYSTR *dystr_create() {
    DYSTR *dystr = malloc(sizeof(DYSTR));
    if (dystr == NULL) return NULL; //malloc produced error
    dystr->data = malloc(sizeof(char) * 1); // '\0'
    if (dystr->data == NULL) {
        free(dystr);
        return NULL; //malloc produced error
    }
    dystr->data[0] = '\0';
    dystr->length = 0;
    dystr->capacity = 1;
    return dystr;
}

int dystr_append(DYSTR *dystr, char c) {
    if (dystr == NULL) return -1; // what?

    size_t required_space = dystr->length + 2; // original + new char + \0

    if (dystr->capacity < required_space) {
        size_t new_capacity = dystr->capacity * 2; // can modify
        if (new_capacity < required_space) new_capacity = required_space; // can over-allocate, but that's alright!

        char *new_data = realloc(dystr->data, sizeof(char) * new_capacity);
        if (new_data == NULL) return 0; //problem reallocating

        dystr->data = new_data;
        dystr->capacity = new_capacity;
    }

    dystr->data[dystr->length] = c;
    dystr->length++;
    dystr->data[dystr->length] = '\0';
    return 1; // success
}

void dystr_free(DYSTR *dystr) {
    if (dystr != NULL) {
        free(dystr->data);
        free(dystr);
    }
}