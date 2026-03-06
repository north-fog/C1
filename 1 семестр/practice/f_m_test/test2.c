#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void bubbleSort2d(int **a, size_t m, size_t n) {
    int tmp;
    size_t i, j, k, jp, ip;
    size_t size = m*n;
    char flag;
 
    do {
        flag = 0;
        for (k = 1; k < size; k++) {
            //Вычисляем индексы текущего элемента
            j = k / m;
            i = k - j*m;
            //Вычисляем индексы предыдущего элемента
            jp = (k-1) / m;
            ip = (k-1) - jp*m;
            if (a[i][j] > a[ip][jp]) {
                tmp = a[i][j];
                a[i][j] = a[ip][jp];
                a[ip][jp] = tmp;
                flag = 1;
            }
        }
    } while(flag);
}
 
#define SIZE_X 3
#define SIZE_Y 4
 
void main() {
    int **a = NULL;
    int i, j;
 
    a = (int**) malloc(sizeof(int*) * SIZE_X);
    for (i = 0; i < SIZE_X; i++) {
        a[i] = (int*) malloc(sizeof(int) * SIZE_Y);
        for (j = 0; j < SIZE_Y; j++) {
            a[i][j] = rand();
            printf("%8d ", a[i][j]);
        }
        printf("\n");
    }
 
    printf("\nafter sort\n");
 
    bubbleSort2d(a, SIZE_X, SIZE_Y);
    for (i = 0; i < SIZE_X; i++) {
        for (j = 0; j < SIZE_Y; j++) {
            printf("%8d ", a[i][j]);
        }
        printf("\n");
    }
 
    for (i = 0; i < SIZE_X; i++) {
        free(a[i]);
    }
    free(a);
 
    _getch();
}