#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

void guessing_game() {
    int rnd = rand() % 1000 + 1;
    int num;
    int count = 0;
    while (1) {
        count++;
        printf("Enter a number (1-1000): ");
        scanf("%d", &num);
        if (num > rnd) {
            printf("Nope, too high!\n");
        } else if (num < rnd) {
            printf("Nope, too low!\n");
        } else {
            printf("Correct, the number is %d! You guessed it right after %d attempts\n", num, count);
            break;
        }
    }
}

void is_arithmetic_progression() {
    int a1, a2;
    printf("Enter the first and second items separated by a comma: ");
    if (scanf("%d, %d", &a1, &a2) != 2) {
        printf("Wrong input! goodbye");
        exit(0);
    }
    int diff = a2 - a1;
    printf("What is the next item? ");
    int input, last_input = a2;
    int flag = 1, count = 2;
    while (scanf("%d", &input) == 1) {
        count++;
        if (input - last_input != diff) {
            flag = 0;
        }
        last_input = input;
        printf("What is the next item? ");
    }
    if (flag) {
        printf("This series of %d items is an arithmetic progression with a1=%d and diff=%d", count, a1, diff);
    } else {
        printf("This series of %d items is not an arithmetic progression", count);
    }
}

void ascii_art() {
    int input;
    printf("Would you like to draw a square (1) or a diamond (2)? ");
    scanf("%d", &input);
    if (input == 1) {
        int edge_size;
        printf("What should be the edge size? (1-30): ");
        scanf("%d", &edge_size);
        if (edge_size < 1 || edge_size > 30) {
            printf("Wrong choice! good bye");
            exit(0);
        }
        for (int i = 0; i < edge_size; ++i) {
            for (int j = 0; j < edge_size; ++j) {
                printf("*");
            }
            printf("\n");
        }

    } else if (input == 2) {
        int diagonal_size;
        printf("What should be the diagonal size? (odd, 1-29): ");
        scanf("%d", &diagonal_size);
        if (diagonal_size < 1 || diagonal_size > 29 | diagonal_size % 2 == 0) {
            printf("Wrong choice! good bye");
            exit(0);
        }
        for (int i = 0; i < diagonal_size; ++i) {
            int spaces = abs(diagonal_size / 2 - i);
            for (int j = 0; j < spaces; ++j) {
                printf(" ");
            }

            int n = (diagonal_size / 2 - spaces) * 2 + 1;
            for (int j = 0; j < n; ++j) {
                printf("*");
            }
            printf("\n");
        }
    } else {
        printf("Wrong choice! good bye");
        exit(0);
    }
}

int main() {
    srand(time(NULL));
    //setbuf(stdout, NULL);
    ascii_art();
    return 0;
}

