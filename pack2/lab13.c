#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void search_substring(const char* substring, int num_files, ...) {
    va_list files;
    va_start(files, num_files);

    for (int i = 0; i < num_files; i++) {
        const char* file_path = va_arg(files, const char*);
        FILE* file = fopen(file_path, "r");

        if (file == NULL) {
            printf("Unable to open file: %s\n", file_path);
            continue;
        }

        char line[BUFSIZ];
        int line_index = 1;
        int found = 0;

        while (fgets(line, sizeof(line), file)) {
            char* position = line;
            int char_index = 0;

            while (*position != '\0') {
                int substring_index = 0;
                int match = 1;

                while (substring[substring_index] != '\0') {
                    if (substring[substring_index] != position[substring_index]) {
                        match = 0;
                        break;
                    }

                    substring_index++;
                }

                if (match) {
                    printf("Substring found in file: %s\n", file_path);
                    printf("Line: %d, Character: %d\n", line_index, char_index + 1);
                    found = 1;
                }

                position++;
                char_index++;
            }

            line_index++;
        }

        if (!found) {
            printf("Substring not found in file: %s\n", file_path);
        }

        fclose(file);
    }

    va_end(files);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <substring> <file1> <file2>\n", argv[0]);
        return 1;
    }

    const char* substring = argv[1];
    int num_files = argc - 2;

    search_substring(substring, num_files, argv[2], argv[3]);

    return 0;
}
