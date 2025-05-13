#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

long file_size(FILE *file) {
    if (!file) { return 0; }
    fpos_t original;
    if (fgetpos(file, &original) != 0) {
        printf("fgetpos() failed: %i\n", errno);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long out = ftell(file);
    if (fsetpos(file, &original) != 0) {
        printf("fsetpos() failed: %i\n", errno);
    }
    return out;
}

char *file_contents(char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Could not open file at %s\n", path);
        return NULL;
    }
    long size = file_size(file);
    char *contents = malloc(size + 1);
    char *write_iter = contents;
    size_t bytes_read = 0;
    while (bytes_read < size) {
        size_t bytes_read_this_iter = fread(write_iter, 1, size - bytes_read, file);
        if (ferror(file)) {
            printf("Error while reading: %i\n", errno);
            free(contents);
            return NULL; 
        }
        bytes_read += bytes_read_this_iter;
        write_iter += bytes_read_this_iter;
        if (feof(file)) { break; }
    }
    if (bytes_read < size) {
        printf("bytes read: %zu, size: %ld\n", bytes_read, size);
        free(contents);
        return NULL;
    }
    contents[size] = '\0';
    return contents;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
        exit(0);
    }
    
    char *path = argv[1];
    char *contents = file_contents(path);
    if (contents) {
        printf("Contents of %s:\n---\n%s\n---\n", path, contents);
    }
	return 0;
}
