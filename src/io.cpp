#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

#include "io.hpp"
#include "utils.hpp"

char *file_to_cstr(const char *filepath) {
    FILE *file = fopen(filepath, "rb");

    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *buffer = (char *)s_malloc(length + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    buffer[length] = '\0';
    return buffer;
}

char get_char(void) {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}
