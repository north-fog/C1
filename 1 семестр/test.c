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

// void main()
// {
//    int N=10,M=20, k=0;
//    for (int i=0, j=0; i < N || j < M; i++, j++ )
//         {
//         k++;
//         }
//     int u=0;     
// int a = 5, b = 7;
// b=a++ + b;
// b=a++ + b;
// a=0;
// int a[11];
// int i, j, s =0;
// for (i =0; i <=10; i++)
// {
//     a[i]=i-1;
// }
// for(i = 0, j =10; i<=j;i++,j--)
// {
//     s = s +(a[j]-a[i]);
// }
// printf("s =%d",s);
// }