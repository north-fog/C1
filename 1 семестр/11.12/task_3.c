#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <Windows.h>    //Билиоткека Windows

int task_3(int **arr, const int n_row, const int n_column)
{   
    int *answer = (int*)malloc(n_row * sizeof(int));
    for(int i = 0; i < n_row; i++)
    {
       int *row = *(arr+i);
       *(answer+i) = *row ;
       for(int j = 1; j < n_column; j++) 
            if (*(row + i) < *(row + i - 1))
            {
                *(answer+i) = *(row + j);
            }
    }
    return answer;
}

void main()
{
    setlocale(LC_ALL, "rus");   //Локализация
    SetConsoleCP(1251);         //Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);  

    int length=5;
    int arr_1[5]={1,4,3,7,5};
    int arr_2[5]={1,4,3,7,5};
    int arr_3[5]={1,4,3,7,5};

    int **arr[]={arr_1, arr_2, arr_1};

    int *answer_3 = task_3( arr, 3, 5);
    for(int j = 0; j < 3; j++)  
        {
        printf("%d\n", *(answer_3+j));
        }
    getchar();
    getchar();
}