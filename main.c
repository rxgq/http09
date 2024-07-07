#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_TOKENS 100
#define MAX_PARAMS 10

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

struct Token* tokenize(char* cptr) {
    struct Token* tokens = (struct Token*)malloc(100 * sizeof(struct Token));
    if (tokens == NULL) {
        perror("Error allocating memory for tokens");
        exit(EXIT_FAILURE);
    }

    const char* delimiter = "\n";
    int token_count = 0;

    char* token = strtok(cptr, delimiter); 
    while (token_count < 100 && token != NULL) {

        char* space = strchr(token, ' ');
        if (space != NULL) {
            int space_idx = (int)(space - token) + 1;
            char* param_str = skip_char(token, space_idx);

            char** params = tokenize_params(param_str);
            strncpy(tokens[token_count].Value, token, sizeof(tokens[token_count].Value) - 1);
            tokens[token_count].Value[sizeof(tokens[token_count].Value) - 1] = '\0';

            tokens[token_count].Params = params;
        }

        token = strtok(NULL, delimiter);
        token_count++;
    }

    for (int i = 0; i < token_count; i++) {
        printf("Token %d: Value=%s, Params=[", i, tokens[i].Value);
        if (tokens[i].Params != NULL) {
            for (int j = 0; tokens[i].Params[j] != NULL; j++) {
                printf("%s%s", tokens[i].Params[j], (tokens[i].Params[j + 1] != NULL) ? ", " : "");
            }
        }
        printf("]\n");
    }

    return tokens;
}

int main() {
    char* cptr = read_source("code.txt");
    struct Token* tokens = tokenize(cptr);


    return 0;
}