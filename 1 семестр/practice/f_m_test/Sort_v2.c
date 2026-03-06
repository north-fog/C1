#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <stdlib.h>     //Билиоткека основыне функции   
#include <Windows.h>    //Билиоткека Windows
#include <time.h>       //Библиотека времени
#include <omp.h>        //Библиотека времени выполнения
#include <malloc.h>


//Помощь
void help()
{
    printf("1 - Сортировка выбором\n");
    printf("2 - Сортировка пузырьком\n");
    printf("3 - Сортировка вставками\n");
    printf("4 - Сортировка Хоара\n");
    printf("5 - Сравнение эффективности\n");
    printf("6 - Новая задача\n");
    printf("7 - Помощь\n");
    printf("0 – Завершить работу\n");
}

//Генерация массива
void generate_arr(int raw_arr[], int size, int lb, int rb)
{   
    srand((unsigned int) time(0));
    for (int i = 0; i < size; i++)
    {
        raw_arr[i] = (rb - lb) * ((double)rand()) / RAND_MAX + lb;
    }

}

// Ввод целого числа с контролем
int input_int(const char name[], int left, int right) 
{
    int res;
    do
    {
        printf("%s", name);
        printf(" (from %d to %d) = ", left, right);
        scanf("%d", &res);
    } while (res < left || res > right);
    return res;
}

//Копирование массива
void copy_array(int raw_arr[],int sort_arr[],int leght)
{   

    for(int i=0;i<leght;i++)
    {
        sort_arr[i]=raw_arr[i];
    }   
}

//Проверка на отсортированость массивов 
int increase_control(int arr[], int count) 
{
    int error = 0;
    for (int i = 0; i < count - 1; i++) {
        if (arr[i] > arr[i+1])
        {
            error = i + 1;
            break;
        }
    }
    return error;
}

//Функция перестановки двух элементов
void swap(int *n1, int *n2)
{
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

//Сортровка выбором
void select_sort(int arr[], int leght)
{    
    printf("Сортировка выбором ------------------------------------------------------\n");  
	unsigned int count = 0;
    unsigned int compare = 0;
    double start_t = omp_get_wtime();
    for (int i = 0; i < leght - 1; i++)
    {
        for (int j = i + 1; j < leght; j++) 
		{
            compare++;
			if (arr[i] > arr[j]) 
			{
                swap(&arr[i], &arr[j]);
				count++;
            }
        }
    }
    double finish_t = omp_get_wtime();
    int control = increase_control(arr, leght);             // контроль сортированности результата
	if ( control > 0 ) 
		printf("Ошибка сортировки на шаге %d\n", control);
    else 
        printf("Перестановок = %10d, сравнений = %10d, время: %15.10lf\n", count, compare, finish_t - start_t);
    
}


//Сортировка пузырьком
void buble_sort(int arr[], int leght)
{   
    printf("Сортировка пузырьком ----------------------------------------------------\n");
    unsigned int count = 0;
    unsigned int compare = 0;
    double start_t = omp_get_wtime();
	for (int i = 0; i < leght - 1; i++) 
	{
		for (int j = 0; j < leght - 1; j++) 
		{   
            compare++;
			if (arr[j + 1] < arr[j])
			{
                swap(&arr[j+1], &arr[j]);
				count++;
			}
		}
	}
    double finish_t = omp_get_wtime();
    int control = increase_control(arr, leght);             // контроль сортированности результата
	if ( control > 0 ) 
		printf("Ошибка сортировки на шаге %d\n", control);
    else
        printf("Перестановок = %10d, сравнений = %10d, время: %15.10lf\n", count, compare, finish_t - start_t);
    
}


//Сортировка вставками
void insert_sort(int arr[], int leght)     
{   
    printf("Сортировка вставками ----------------------------------------------------\n");
	unsigned int count = 0;
    unsigned int compare = 0;
    int temp, iter;
    double start_t = omp_get_wtime();
    for (int i = 1; i < leght; i++) {
        temp = arr[i];
        iter = i;
        while (iter > 0)
		{   
            compare++;
			if (temp < arr[iter-1]) 
			{
				arr[iter] = arr[iter-1];
                count++;
				iter--;
			}
			else
				break;
        }
        arr[iter] = temp;
        count++;
    }
    double finish_t = omp_get_wtime();
    int control = increase_control(arr, leght);             // контроль сортированности результата
	if ( control > 0 ) 
		printf("Ошибка сортировки на шаге %d\n", control);
    else
        printf("Перестановок = %10d, сравнений = %10d, время: %15.10lf\n", count, compare, finish_t - start_t);
}


// сортировка Хоара по возврастанию
void quick_sort(int arr[], int first, int last,int  *count, int *compare) 
{   
    int i = first, j = last;
	int x = arr[(first + last) / 2];
	do {
		while (arr[i] < x)
        {
			i++;
            (*compare)++;
		}
		while (arr[j] > x)
        {
			j--;
            (*compare)++;
		}
		if (i <= j) 
		{
			if (i != j && arr[i] != arr[j])
			{
				swap(&arr[i], &arr[j]);
				(*count)++;
			}
			i++;  
            j--;
		}
	} while (i <= j);

	if (i < last)
		quick_sort(arr, i, last, count, compare);
	if (first < j)
		quick_sort(arr, first, j, count, compare);
}


//вызов сортировки Хоара по возрастанию
void inv_quick_sort(int arr[], int first, int leght)
{   
    printf("Быстрая сортировка ------------------------------------------------------\n");
    unsigned int count = 0;
    unsigned int compare = 0;
    double start_t = omp_get_wtime();
    quick_sort(arr, first, leght, &count, &compare);
    double finish_t = omp_get_wtime();
    int control = increase_control(arr, leght);             // контроль сортированности результата
	if ( control > 0 ) 
	    printf("Ошибка сортировки на шаге %d\n", control);
    else
        printf("Перестановок = %10d, сравнений = %10d, время: %15.10lf\n", count, compare, finish_t - start_t);
}


void main()
{
setlocale(LC_ALL, "rus");   //Локализация
SetConsoleCP(1251);         //Установка кодовой страницы win-cp 1251 в поток ввода
SetConsoleOutputCP(1251);

int leght;                          	//Реальная длина сортируемого массива
int l_side, r_side;                     //Левая и правая граница массива
int answer;                             //Выбор пользователя
int sort_arr_2[20000];

leght = input_int("К-во элементов массива: ", 2, 20000);                //Ввод длины массива
l_side = input_int("Левая граница диапазона = ", -5000, 4900);          //Ввод левой границы диопазана генерации чисел 
r_side = input_int("Правая граница диапазона = ", l_side + 2, 5000);    //Ввод правой границы диопазана генерации чисел

int *raw_arr = (int*)malloc(leght * sizeof(int));
int *sort_arr = (int*)malloc(leght * sizeof(int));

generate_arr(raw_arr,leght, l_side, r_side);            //Генерация массива
help();                                         //Вывод помощи

do{ 
    printf("_________________________________________________________________________\n");
    printf("Выберите действиe (7 - список команд)\n");
    printf("_________________________________________________________________________\n");

    scanf("%d",&answer);
    switch(answer)
    {
        case 1:
            copy_array(raw_arr,sort_arr,leght);       
            select_sort(sort_arr, leght);
            break;
        case 2:
            copy_array(raw_arr,sort_arr,leght);   
            buble_sort(sort_arr, leght);
            break;
        case 3:
            copy_array(raw_arr,sort_arr,leght);   
            insert_sort(sort_arr, leght);
            // for(int i=0;i<leght;i++)
            // {
            //     printf("%d ,",raw_arr[i]);
            // }
            break;
        case 4:
            copy_array(raw_arr,sort_arr,leght);  
            inv_quick_sort(sort_arr, 0, leght); 
            break;
        case 5:
            copy_array(raw_arr,sort_arr,leght);    
            select_sort(sort_arr, leght);
            copy_array(raw_arr,sort_arr,leght); ;  
            buble_sort(sort_arr, leght);
            copy_array(raw_arr,sort_arr,leght);    
            insert_sort(sort_arr, leght);
            copy_array(raw_arr,sort_arr,leght);  
            inv_quick_sort(sort_arr, 0, leght);
            printf("<<<<--------------------------------------------------->>>>\n");
            copy_array(raw_arr,sort_arr_2,leght);    
            select_sort(sort_arr_2, leght);
            copy_array(raw_arr,sort_arr_2,leght); ;  
            buble_sort(sort_arr_2, leght);
            copy_array(raw_arr,sort_arr_2,leght);    
            insert_sort(sort_arr_2, leght);
            copy_array(raw_arr,sort_arr_2,leght);  
            inv_quick_sort(sort_arr_2, 0, leght);
            break;   
        case 6:
            leght = input_int("К-во элементов массива ", 2, 20000);
            l_side = input_int("Левая граница диапазона ", -5000, 4900);
            r_side = input_int("Правая граница диапазона ", l_side + 2, 5000);
            generate_arr(raw_arr, leght, l_side, r_side);
            break;
        case 7:   
            help();
            break;
    }
}while(answer!=0);
printf("Конец работы");
}