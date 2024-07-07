#include <stdio.h>
#include <stdlib.h> 

int main() {
    FILE *fptr = fopen("code.txt", "r");
    char* buff = NULL;
    long size;

    if (fptr == NULL) {
        perror("Error opening file.");
        return 1;
    }

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    if (size == -1) {
        perror("Error getting file size");
        fclose(fptr);
        return 1;
    }

    if (fseek(fptr, 0, SEEK_SET) != 0) {
        perror("Error seeking to start of file");
        fclose(fptr);
        return 1;
    }

    // + 1 for null terminator
    buff = (char *)malloc(size + 1);
    if (buff == NULL) {
        perror("Error allocating memory for asm");
        fclose(fptr);
        return 1;
    }

    if (fread(buff, sizeof(char), size, fptr) != size) {
        perror("Error reading file");
        free(buff);
        fclose(fptr);
        return 1;
    }

    buff[size] = '\0';
    fclose(fptr);

    printf("File contents:\n%s\n", buff);

    free(buff);
    return 0;
}