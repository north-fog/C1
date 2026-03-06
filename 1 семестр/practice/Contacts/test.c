#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <stdlib.h>     //Билиоткека основыне функции   
#include <Windows.h>    //Билиоткека Windows

void main()
{
int i1, i2, i3;
int *p1, *p2, *p3;
i1 = 1; i2 = 2; i3 = 3;
p1 = &i1;
p2 = &i2;
p3 = &i3;
*p1 = i1 + i2;
*p2 += 1;
*p3 = *p1 + *p2;
printf("%d %d %d", i1, i2, i3);
}