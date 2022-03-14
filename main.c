#include <stdio.h>
#include <limits.h>
int main() {
    int num;
    setbuf(stdout, NULL);
    printf("Enter an integer: \n");
    int min = INT_MAX, max = INT_MIN;
    while (scanf("%d", &num) != -1) {
        if (min > num) {
            min = num;
        }
        if (max < num) {
            max = num;
        }
        printf("Enter an integer: \n");
    }

    printf("Max was: %d\n", max);
    printf("Min was: %d\n", min);
}
