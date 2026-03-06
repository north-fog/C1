#include <stdio.h>   // Библиотека ввода-вывода
#include <locale.h>  // Библиотека кириллиц (локализации)
void main()
{
    /*
    Програма сравниевт 3 числа и выводит их в порядке убывания
    */
    setlocale(LC_CTYPE, "Ru_RU.UTF-8");//локализация

    int x,y,z;//числа

    //ввод данных
    printf("Введите x: ");
    scanf("\n%d",&x,"\n");
    printf("Введите y: ");
    scanf("\n%d",&y,"\n");
    printf("Введите z: ");
    scanf("\n%d",&z,"\n");

    //Сравнение чисел и ввывод их в порядуе убывния
    if (x>=y && x>=z)
        {
        printf("%d",x);
        if (y>=z)
            printf("%d%d",y,z);
        else
            printf("%d%d",z,y);
        }
    else if (y>x && y>z)
        {
        printf("%d",y);
        if (x>=z)
            printf("%d%d",x,z);
        else
            printf("%d%d",z,x);
        }
    else if (z>x && z>y)
        {
        printf("%d",z);
        if (x>=y)
            printf("%d%d",x,y);
        else
            printf("%d%d",y,x);
        }
getchar();
getchar();
}