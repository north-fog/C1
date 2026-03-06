#include <stdio.h>      //Билиоткека ввода вывода 
#include <locale.h>     //Билиоткека локализации
#include <stdlib.h>     //Билиоткека основыне функции   
#include <Windows.h>    //Билиоткека Windows

// class Rational
// {
//     public:
//         int num;
//         int den;
// };

void main()
{
    setlocale(LC_ALL, "rus");   //Локализация
    SetConsoleCP(1251);         //установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);

    int a, b, c;
    cout << "Введите значения a, b и c:";
    cin >> a >> b >> c;
    cout << "a = " << a << ", b = " << b << ", c = " << c;

}