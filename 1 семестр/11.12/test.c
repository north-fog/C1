#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <Windows.h>    //Билиоткека Windows

int task_1(int *arr, const int length)
{   
    int count = 0;
    for(int i=1;i < length;i++)
    {
        if (*(arr+i) < *(arr+i-1))
            count++;
    }
    return count;
}

int task_2(int *arr, const int length)
{
    int count = 0;
    for(int i=1;i < length-1;i++)
    {
        if ((arr[i-1] < arr[i])&&(arr[i] > arr[i+1]))
            count++;
    }
    return count;
}


int task_3(int matrix[], int length)
{
    for(int i =0;i<length;i++)
    {   
        answer_3[i] = matrix[i][0];
        for(int j = 1; j < length; j++)
        {
            if((matrix[i][j]) < (answer_3[i]))
                answer_3[i] =matrix[i][j];
            
        }
    }

}

void main()
{
    setlocale(LC_ALL, "rus");   //Локализация
    SetConsoleCP(1251);         //Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);  

    int length;

    printf("Введите длину массива: ");
    scanf("%d", &length);

    int *arr = (int*)malloc(length * sizeof(int));

    printf("Введите числа массива: ");
    for(int i=0;i<length;i++)
    {
        scanf("%d", arr[i]);
    }

    int answer_1 = task_1( arr, length);

    printf("Введите длину массива: ");
    scanf("%d", &length);

    arr = (int*)malloc(length * sizeof(int));
    printf("Введите числа массива: ");
    for(int i=0;i<length;i++)
    {
        scanf("%d",arr[i]);
    }

    int answer_2 = task_2(arr, length);

    int matrix[5][5];

    int *answer_3=(int*)malloc(5 * sizeof(int));




}