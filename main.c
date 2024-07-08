#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

struct Token {
    char Value[4];
    char** Params;
};

char* read_source(const char* filename) {
    FILE *fptr = fopen(filename, "rb");

    if (!fptr) {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    // + 1 for null terminator
    char *buff = (char *)malloc(size + 1);
    if (buff == NULL) {
        perror("Error allocating memory for asm");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    fread(buff, sizeof(char), size, fptr);
    buff[size] = '\0';

    fclose(fptr);

    return buff;
}

char *skip_char(char *s, size_t n) {
    while (*s && n--)
        s++;
    return s;
}

void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

char** tokenize_params(const char* param_str) {
    char** params = (char **)malloc(2 * sizeof(char*));
    const char* delimiter = ",";

    char* copy = strdup(param_str);
    if (copy == NULL) {
        perror("Error allocating memory for param_str copy");
        exit(EXIT_FAILURE);
    }

    int param_count = 0;
    char* param = strtok(copy, delimiter);
    while (param != NULL) {
        remove_spaces(param); 
        params[param_count] == strdup(param);
        param = strtok(NULL, delimiter);
        param_count++;
    }

    return params;
}

char* substr(char* str, int start, int end) {
    char* sptr = (char*)malloc((end - start + 1) * sizeof(char));
    if (!sptr) return NULL;

    strncpy(sptr, str + start, end - start);
    sptr[end - start] = '\0';

    return sptr;
}

char** tokenize(char* cptr) {
    char** tokens = (char **)malloc(64 * sizeof(char *));
    const char* delimiter = "\n";
    int token_count = 0;

    char* token = strtok(cptr, delimiter); 
    while (token_count < 100 && token != NULL) {
        char* space_idx = strchr(token, ' ');
        int index = (int)(space_idx - token) + 1;

        int length = strlen(token) - index;
        char* param_str = substr(token, index, index + length);


        tokens[token_count++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    for (int i = 0; i < token_count; i++) {
        // printf("%d ", i);
        // printf("%s\n", tokens[i]);
    }

    return tokens;
}

int main() {
    char* cptr = read_source("code.txt");
    char** tokens = tokenize(cptr);


    return 0;
}