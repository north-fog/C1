#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <Windows.h>    //Билиоткека Windows

int task_2(int *arr, const int length)
{   
    int count = 0;
    for(int i=1;i < length-1;i++)
    {
        if ((*(arr + i - 1) < *(arr + i)) && (*(arr + i) > *(arr + i + 1)))
            count++;
    }
    return count;
}

void main()
{
    setlocale(LC_ALL, "rus");   //Локализация
    SetConsoleCP(1251);         //Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);  

    int length=5;
    int arr[5]={1,4,6,7, 5};

    int answer_1 = task_1( &arr, length);
    printf("%d", answer_1);
    getchar();
    getchar();
}