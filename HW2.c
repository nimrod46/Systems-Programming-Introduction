//
// Created by Nimrod Machlav
// Id: 315230185

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>


void validate_reduce_method(int *arr, int size);

/**
 * Checks if email length is legal
 * @param size length of the email address
 * @return True if legal, otherwise false
 */
bool is_legal_email_length(unsigned long size);

/**
 * Finds and validates that the at sign (@) appears only once
 * @param email_to_check email as char array to validate
 * @param size length of the email address
 * @return The at sign index if at sign exists one, otherwise 0
 */
int get_at_sign_index(const char *email_to_check, unsigned long size);

/**
 * Validates that string contains only alphabetic characters and digits up to "end_index" (exclude)
 * @param str char array
 * @param end_index int end index to check
 * @return True if str is valid, otherwise false
 */
bool contains_alpha_and_digit_only(const char *str, int end_index);

/**
 * Validates the str only contains dots and alphabetic letters starting from start_index (include)
 * @param str char array to validate
 * @param size length of str
 * @param start_index int start index to validate from
 * @return True if str is valid, otherwise false
 */
bool contains_dots_and_alpha_only(const char *str, unsigned long size, int start_index);

/**
 * Finds if two equal sequential items in array exists
 * @param array int array
 * @param size array size
 * @return The index to the first item if any exists, otherwise -1
 */
int same_value(const int *array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (array[i] == array[i + 1]) {
            return i;
        }
    }
    return -1;
}

/**
 * Counts all two items that sums up to the target
 * @param array int array
 * @param size array size
 * @param target sum target to find
 * @return The count
 */
int sum_n(const int *array, int size, int target) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size - i; ++j) {
            if (array[i] + array[j] == target) {
                count++;
            }
        }
    }
    return count;
}

/**
 * Removes all zeros from the array, this function will remove zeros from the given array without effecting the order
 * @param array int array
 * @param size array size
 * @return The length of the array
 */
int reduce(int *array, int size) {
    int zero_count = 0;
    for (int i = 0; i < size - zero_count; ++i) {
        if (array[i] == 0) {
            int index = i;
            int current_zero_count = 0;
            while (1) { //Find all sequential zeros
                if (index >= size - zero_count || array[index] != 0) {
                    break;
                }
                index++;
                current_zero_count++;
            }
            zero_count += current_zero_count;
            for (int j = i; j < size - zero_count; ++j) {
                array[j] = array[j + current_zero_count];
            }
        }
    }
    return size - zero_count;
}

/**
 * Validates if the given email is a legal email
 * @param email_to_check char array
 * @return True if legal, otherwise false
 */
bool is_legal_email(const char *email_to_check) {

    unsigned long size = strlen(email_to_check);
    if (!is_legal_email_length(size)) {
        return false;
    }

    int at_sign_index = get_at_sign_index(email_to_check, size);

    if (at_sign_index == 0) {
        return false;
    }

    if (!contains_alpha_and_digit_only(email_to_check, at_sign_index)) {
        return false;
    }

    return contains_dots_and_alpha_only(email_to_check, size, at_sign_index);
}

/**
 * Checks if two emails are identical without case sensitivity
 * @param email1 char array
 * @param email2 char array
 * @return True if emails are the same, otherwise false
 */
bool is_same_email(const char *email1, const char *email2) {
    unsigned long size1 = strlen(email1);
    unsigned long size2 = strlen(email2);

    if (size1 != size2) {
        return false;
    }

    for (int i = 0; i < size1; ++i) {
        if (tolower(email1[i]) != tolower(email2[i])) {
            return false;
        }
    }
    return true;
}

//int main() {
//    int arr[] = {1, 0, 5, 8, 0, 0};
//    int size = 6;
//    assert(same_value(arr, size) == 4);
//
//    assert(sum_n(arr, size, 8) == 1);
//
//    validate_reduce_method(arr, size);
//
//    int arr2[] = {0, 1, 5, 8, 5, 0};
//
//    validate_reduce_method(arr2, size);
//
//    int arr3[] = {0, 0, 0, 0, 0, 0};
//
//    validate_reduce_method(arr3, size);
//    int arr4[] = {0, 0, 0, 0, 0, 4};
//
//    validate_reduce_method(arr4, size);
//
//    char *email1 = "nimrodma99@gmail.com";
//    assert(is_legal_email(email1));
//
//    char *email2 = "nimrodma99@gma.il.co";
//    assert(is_legal_email(email2));
//
//    char *email3 = "nIMRODMa99@gmail.coM";
//    assert(is_same_email(email1, email3));
//
//    printf("PASS");
//    return 0;
//}

void validate_reduce_method(int *arr, int size) {
    int zero_count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == 0) {
            zero_count++;
        }
    }

    int new_size = reduce(arr, size);
    assert(new_size == size - zero_count);

    for (int i = 0; i < new_size; ++i) {
        assert(arr[i] != 0);
    }
}

bool is_legal_email_length(unsigned long size) {
    return size <= 20;
}


int get_at_sign_index(const char *email_to_check, unsigned long size) {
    bool contains_at = false;
    int at_sign_index = 0;
    for (int i = 0; i < size; ++i) {
        if (email_to_check[i] == '@') {
            if (contains_at) {
                return 0;
            }
            at_sign_index = i;
            contains_at = true;
        }
    }
    return at_sign_index;
}


bool contains_alpha_and_digit_only(const char *str, int end_index) {
    for (int i = 0; i < end_index; ++i) {
        if (!isalpha(str[i]) && !isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


bool contains_dots_and_alpha_only(const char *str, unsigned long size, int start_index) {
    bool contains_dot = false;
    for (int i = start_index + 1; i < size; ++i) {
        if (str[i] == '.') {
            contains_dot = true;
        } else if (!isalpha(str[i])) {
            return false;
        }
    }
    return contains_dot;
}


