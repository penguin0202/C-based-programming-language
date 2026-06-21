typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} DYSTR;

DYSTR *dystr_create();
int dystr_append(DYSTR *dystr, char c);
void dystr_free(DYSTR *dystr);
char *dystr_convert(DYSTR *dystr);