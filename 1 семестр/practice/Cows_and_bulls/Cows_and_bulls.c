#include <stdio.h>   // Библиотека ввода-вывода
#include <locale.h>  // Библиотека локализация
#include <stdlib.h>  // Библиотека стнадартных функций 
#include <time.h>    // Библиотека работы со временем 
#include <math.h>    // Библиотека основных математических функций

/*
    Программа, реализующует игру «Быки и коровы».
    Программа Генерирует число заданой длины из неповторяющихся цифр,
    Пользователь должен угать загаданае число

*/

//Проверка на повторяющеися цифры
int check(int value, int arr[], int count)
{
    for(int i = count-1; i>=0; i--)
        {
            if (value==arr[i])
                return 1;
        }
    return 0;
}


void main()
{
    srand(time(NULL));                  //Задаем зерно рандома через время
    int arr[5];                         //Массив с загадаными числами
    int answer[5];                      //Массив с числами пользователя
    int size;                           //Переменая для длины числа 
    int p_num;                          //Число игрока
    int cow = 0, bull = 0, atempt = 0;  //Переменые коров, быков, попыток
    int test = 0;                       //Переход в режим разработчика (0 - обычная игра, 1 - режим разработчика)
    int flag;                           //Переменая для цикла while  
    char ch;                            //Служебная переменная ввода

    setlocale(LC_CTYPE, "Ru_RU.UTF-8"); //локализация

    if(test==1)
        printf("Включён режим разработчика\n");

    //Ввод длины числа с проверкой
    printf("Введите длину числа от 2 до 5: ");
    while (scanf("%d",&size) == 0 || (size<2)||(size>5))
    {
       printf("Вы ввели некорктное значение. Попробуйте еще раз: ");    
       while(ch = getchar() != '\n' ); 
    }
    while(ch = getchar() != '\n' ); 


    //Герирование числа которое должен угадать игрок
    for(int i = 0; i<size; i++)
    {   
        do
        {
            arr[i]= rand()%10;
        } while(check(arr[i], arr, i));
    }   


    //Алгоритм игры
    do{
        cow=bull=0;     //обнуление коров и быков

    //Ввод ответа игрока и его проверка 
        do
        {   
            printf("Ведите число (число дополняется нулями слева до нужной длины): ");
            while (scanf("%d",&p_num) == 0 || p_num>=pow(10,size))
            {
                printf("Вы ввели некорктное значение. Попробуйте еще раз: ");    
                while(ch = getchar() != '\n' ); 
            }
            while(ch = getchar() != '\n' ); 
            flag = 0;  
    //Переносим число в массив        
            for (int i = size-1; i>=0; i--)
            {   
                answer[i]=p_num%10;
                p_num=p_num/10;
            }
    //Проверяем на дубли цифр в числе       
            for (int i=0; i<size; i++)
            {    
                if(check(answer[i], answer ,i))
                {
                    printf("В последовательности есть повторяющиеся цифры\n");
                    flag = 1;
                    break;
                }
            }        
        }
        while (flag);

    //Вывод доп. данных в режиме разработчика
        if (test==1)
        {
            for(int i = 0; i<size; ++i) 
            { 
                printf("%d ", arr[i]); 
            }
            printf("| ");
            for(int i = 0; i<size; ++i) 
            { 
                printf("%d ", answer[i]); 
            }
            printf("\n");
        }

    //Выевление быков и коров
        for (int i = 0; i<size; i++)
        {
            if (answer[i]==arr[i])
            {
                bull++;
            }
            else
            {   
                for(int e = 0; e<size; e++)
                {
                    if (answer[i]==arr[e])
                        cow++;
                }    
            }
        }

    //Вывод количества коров и быков
        printf("Результат: ");
        if (cow == 1)
            printf("%d «корова»", cow);
        else if (cow == 5 || cow == 0)
            printf("%d «коров»", cow);
        else    
            printf("%d «коровы»", cow);
        printf(" и ");
        if(bull==0||bull==5)
            printf("%d «быков»\n", bull);
        else if(bull==1)
            printf("%d «бык»\n", bull);
        else
            printf("%d «быка»\n", bull);

        atempt++;   //Добовление 1 к счечику попыток

    }while(bull!=size);

    printf("Вы победили. Количество попыток - %d. Игра окончена.", atempt);

    getchar();  //остановка программы до ввода любого символа
    getchar();
}