#include "io.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file_to_string(char *input_path) {
    char *buffer = 0;
    long length;
    FILE *file = fopen(input_path, "r");

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, file);
        } else {
            printf("File is empty.\n");
            exit(1);
        }
        fclose(file);
    } else {
        printf("Something went wrong opening file '%s'\n", input_path);
        exit(1);
    }

    return buffer;
}
