#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MEMORY_SIZE 65536

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

int main() {
    char* cptr = read_source("code.txt");
    //printf("%s", cptr);

    char* tokens[64]; // experimental
    const char* delimiter = "\n";
    int token_count = 0;

    char* token = strtok(cptr, delimiter); 
    while (token_count < 100 && token != NULL) {
        tokens[token_count++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    for (int i = 0; i < token_count; i++) {
        printf("%d ", i);
        printf("%s\n", tokens[i]);
    }

    free(cptr);

    return 0;
}