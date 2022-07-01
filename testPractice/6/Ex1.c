//
// Created by nimrod on 01/07/2022.
//

#include <stdbool.h>
#include <stdio.h>

void* find_max(void* arr[], int n, bool (*is_bigger)(void* e1, void* e2)) {
    void * max = arr[n-1];
    n--;
    while(n != 0) {
        if(is_bigger(arr[n-1], max)) {
            max = arr[n-1];
        }
        n--;
    }
    return max;
}

bool bt(void* e1, void* e2) {

    return *(int*) e1 > *(int*) e2;
}

int main() {


    int i1 = 10;
    int i2 = 7;
    int i3 = 5;
    int *arr[] = {&i1,&i2,&i3};
    printf("%d", *(int*)find_max((void**)arr, 4, bt));
}