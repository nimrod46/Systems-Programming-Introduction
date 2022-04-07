//
// Created by nimrod on 05-Apr-22.
//
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>

void print_file_info(const char *name, unsigned int lines_count, unsigned int words_count,
                     unsigned int char_count);

unsigned int my_strlen(const char str[]) {
    unsigned int size = 0;
    while (str[size] != '\0') {
        size++;
    }
    return size;
}

void my_strcat(char dest[], const char src[]) {
    unsigned int dest_size = my_strlen(dest);
    unsigned int src_size = my_strlen(src);
    for (int i = 0; i <= src_size; ++i) {
        dest[dest_size + i] = src[i];
    }
}

bool starts_with(const char s[], const char prefix[]) {
    unsigned int prefix_size = my_strlen(prefix);
    for (int i = 0; i < prefix_size; ++i) {
        if (prefix[i] != s[i]) {
            return false;
        }
    }
    return true;
}

unsigned int num_words(const char words[]) {
    unsigned int words_size = my_strlen(words);
    unsigned int words_count = 0;
    char last_char = ' ';
    for (int i = 0; i < words_size; ++i) {
        if (isspace(last_char) && !isspace(words[i])) {
            words_count++;
        }
        last_char = words[i];
    }
    return words_count;
}

char *get_chapter_file_name(const char s[], const char prefix[], const char suffix[]) {
    unsigned int s_size = my_strlen(s);
    unsigned int prefix_size = my_strlen(prefix);
    unsigned int suffix_size = my_strlen(suffix);

    unsigned total_size = s_size + prefix_size + suffix_size + 1;
    char *title = calloc((total_size) , sizeof(char));
    if (!title) {
        printf("Failed to allocate %lu bytes", sizeof(char) *  total_size);
        exit(1);
    }
    for (int i = 0; i < prefix_size + 1; ++i) {
        title[i] = prefix[i];
    }
    bool trimming_mode = true;
    for (int i = s_size - 1; i >= 0; --i) {
        char c = s[i];
        if (!isspace(c)) {
            trimming_mode = false;
            title[i + prefix_size] = s[i];
        } else if (!trimming_mode) {
            title[i + prefix_size] = '-';
        }
    }

    my_strcat(title, suffix);
    return title;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    char *name = argv[1];
    char *output_prefix = argv[2];
    char *output_suffix = ".txt";
    if (argc > 3) {
        output_suffix = argv[3];
    }

    char *file_name = get_chapter_file_name("PREFACE", output_prefix, output_suffix);
    FILE *f_in = fopen(name, "r"), *f_out = fopen(file_name, "w");
    char *buf = NULL;
    size_t buf_size = 0;

    if (!f_in || !f_out) {
        printf("Failed to open files: %s or %s", name, file_name);
        return 2;
    }

    unsigned int current_lines_count = 0;
    unsigned int current_words_count = 0;
    unsigned int current_char_count = 0;

    unsigned int total_lines_count = 0;
    unsigned int total_words_count = 0;
    unsigned int total_char_count = 0;

    while (getline(&buf, &buf_size, f_in) != EOF) {
        if (starts_with(buf, "CHAPTER")) {
            print_file_info(file_name, current_lines_count, current_words_count, current_char_count);
            total_lines_count += current_lines_count;
            total_words_count += current_words_count;
            total_char_count += current_char_count;
            current_lines_count = 1;
            current_words_count = num_words(buf);
            current_char_count = my_strlen(buf);
            free(file_name);
            file_name = get_chapter_file_name(buf, output_prefix, output_suffix);
            fclose(f_out);
            f_out = fopen(file_name, "w");
            if (!f_out) {
                printf("Failed to create file: %s", file_name);
                return 3;
            }
            continue;
        }
        current_lines_count++;
        current_words_count += num_words(buf);
        current_char_count += my_strlen(buf);
        fprintf(f_out, "%s", buf);
    }
    print_file_info(file_name, current_lines_count, current_words_count, current_char_count);
    free(file_name);

    total_lines_count += current_lines_count;
    total_words_count += current_words_count;
    total_char_count += current_char_count;
    fclose(f_in);
    fclose(f_out);
    free(buf);

    print_file_info("Total", total_lines_count, total_words_count, total_char_count);
}

void print_file_info(const char *name, unsigned int lines_count, unsigned int words_count, unsigned int char_count) {
    printf("%-30s: ", name);
    printf("%d linse, ", lines_count);
    printf("%d words, ", words_count);
    printf("%d characters", char_count);
    printf("\n");
}

