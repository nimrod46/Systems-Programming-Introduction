//
// Created by nimrod on 05-Apr-22.
//
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>

/**
 * Prints chapter information as instructed in the assignment
 * @param name : Chapter name
 * @param lines_count : Chapter lines count
 * @param words_count : Chapter words count
 * @param char_count : Chapter char count
 */
void print_chapter_info(const char *name, unsigned int lines_count, unsigned int words_count,
                        unsigned int char_count);
/**
 * Generates chapters by searching for "CHAPTER" in each line
 * @param src_file_name : src file name
 * @param output_prefix : prefix for each generated chapter file
 * @param output_suffix : suffix for each generated chapter file
 */
void generate_chapters(const char *src_file_name, const char *output_prefix, const char *output_suffix);

/**
 * Trims dest string at the end, replaces all other white spaces with "char_replace"
 * @param dest : destination string
 * @param src : source string to copy from
 * @param char_replace : char replace for in string spaces
 */
void trim_and_replace_spaces(char *dest, const char *src, char char_replace);
/**
 * My impl for strlen
 * @param str : string
 * @return : length if the given str
 */
unsigned int my_strlen(const char str[]) {
    unsigned int size = 0;
    while (str[size] != '\0') {
        size++;
    }
    return size;
}

/**
 * My impl for strcat - copy src string to the end of dest string
 * @param dest : destination string
 * @param src : source string
 */
void my_strcat(char dest[], const char src[]) {
    unsigned int dest_size = my_strlen(dest);
    unsigned int src_size = my_strlen(src);
    for (int i = 0; i <= src_size; ++i) {
        dest[dest_size + i] = src[i];
    }
}

/**
 *
 * @param s : string to check
 * @param prefix : string
 * @return true if "s" contains the prefix, "prefix", otherwise false.
 */
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
    char *title = calloc(total_size, sizeof(char));
    if (!title) {
        fprintf(stderr, "Failed to allocate %lu bytes", sizeof(char) * total_size);
        exit(1);
    }
    for (int i = 0; i < prefix_size; ++i) {
        title[i] = prefix[i];
    }

    trim_and_replace_spaces(title, s, '-');

    my_strcat(title, suffix);
    return title;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    if (argc <= 2) {
        fprintf(stderr, "\nUsage: %s <file-path> <output-prefix> [output-suffix] \n", argv[0]);
        return 1;
    }
    setbuf(stdout, NULL);
    char *src_file_name = argv[1];
    char *output_prefix = argv[2];
    char *output_suffix = ".txt";
    if (argc > 3) {
        output_suffix = argv[3];
    }

    generate_chapters(src_file_name, output_prefix, output_suffix);
    return 0;
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"

void generate_chapters(const char *src_file_name, const char *output_prefix, const char *output_suffix) {
    char *dest_file_name = get_chapter_file_name("PREFACE", output_prefix, output_suffix);
    FILE *f_in = fopen(src_file_name, "r"), *f_out = fopen(dest_file_name, "w");
    char *buf = NULL;
    size_t buf_size = 0;

    if (!f_in || !f_out) {
        fprintf(stderr, "Failed to open files: %s , %s\n", src_file_name, dest_file_name);
        exit(2);
    }

    unsigned int current_lines_count = 0;
    unsigned int current_words_count = 0;
    unsigned int current_char_count = 0;

    unsigned int total_lines_count = 0;
    unsigned int total_words_count = 0;
    unsigned int total_char_count = 0;

    while (getline(&buf, &buf_size, f_in) != EOF) {
        if (starts_with(buf, "CHAPTER")) {
            print_chapter_info(dest_file_name, current_lines_count, current_words_count, current_char_count);
            total_lines_count += current_lines_count;
            total_words_count += current_words_count;
            total_char_count += current_char_count;
            current_lines_count = 0;
            current_words_count = 0;
            current_char_count = 0;
            free(dest_file_name);
            dest_file_name = get_chapter_file_name(buf, output_prefix, output_suffix);
            fclose(f_out);
            f_out = fopen(dest_file_name, "w");
            if (!f_out) {
                fprintf(stderr, "Failed to create file: %s", dest_file_name);
                exit(3);
            }
        }
        current_lines_count++;
        current_words_count += num_words(buf);
        current_char_count += my_strlen(buf);
        fprintf(f_out, "%s", buf);
    }
    fclose(f_in);
    fclose(f_out);
    free(buf);

    print_chapter_info(dest_file_name, current_lines_count, current_words_count, current_char_count);
    free(dest_file_name);

    total_lines_count += current_lines_count;
    total_words_count += current_words_count;
    total_char_count += current_char_count;

    print_chapter_info("Total", total_lines_count, total_words_count, total_char_count);
}

#pragma clang diagnostic pop

void trim_and_replace_spaces(char *dest, const char *src, char char_replace) {
    unsigned int dest_size = my_strlen(dest);
    unsigned int src_size = my_strlen(src);
    bool trimming_mode = true; //Trimming mode for the white spaces at the beginning
    for (int i = src_size - 1; i >= 0; --i) {
        char c = src[i];
        if (!isspace(c)) {
            trimming_mode = false;
            dest[i + dest_size] = c;
            continue;
        }
        if (!trimming_mode) {
            dest[i + dest_size] = char_replace;
        }
    }
}

void print_chapter_info(const char *name, unsigned int lines_count, unsigned int words_count, unsigned int char_count) {
    printf("%-30s: ", name);
    printf("%d lines, ", lines_count);
    printf("%d words, ", words_count);
    printf("%d characters", char_count);
    printf("\n");
}

