#include <iostream>     //Библиотека ввода-вывода
#include <fstream>		//Библиотека ввода-вывода
#include "Integral_Sergeev.h" 	//Заголовочный файл вектора
#include <cmath> 
#include <cstring>
using namespace std;

#pragma once

// Конструдтор по умолчанию
Integral::Integral()
{

}

// Задача пределов интегрирования 
void Integral::Set_limit(int a, int b)
{
    low_limit = a;
    up_limit = b;
}
// Задача кол-во разбиений
void Integral::Set_div(int div)
{
    n =div;
}

// Задача функции
void Integral::Set_func(const char* _func)
{
    if (strcmp (_func, "sin") == 0)
    {
        i_func = sin ;
    }
    else if (strcmp (_func, "cos") == 0)
    {
        i_func = cos;
    }
    else if (strcmp (_func, "exp") == 0)
    {
        i_func = exp;
    }
    else
    {
        cout << "Не верно указана функция" << endl;
    }
}

// Задача метода интегрирования 
void Integral::Set_metod(const char* _metod)
{
    if (strcmp (_metod, "middle") == 0)
    {
        i_method = middle ;
    }
    else if (strcmp (_metod, "right") == 0)
    {
        i_method = right;
    }
    else if (strcmp (_metod, "left") == 0)
    {
        i_method = left;
    }
    else
    {
        cout << "Не верно указан метод" << endl;
    }
}

// Метод средних прямоугльников
double Integral::Midpoint()
{   intgr = 0;
    double h = (up_limit - low_limit) / n;
    double result = 0;
    for (int i = 0; i < n; i++) 
    {
        if (i_func == sin)
            result += std::sin(low_limit + (i + 0.5) * h);
        else if (i_func == cos)
            result += std::cos(low_limit + (i + 0.5) * h);
        else if (i_func == exp)
            result += std::exp(low_limit + (i + 0.5) * h);

        
    }
    intgr = result * h;
    return result * h;
}

// Метод левых прямоугльников
double Integral::Leftpoint()
{   intgr = 0;
    double h = (up_limit - low_limit) / n;
    double result = 0;
    for (int i = 0; i < n; i++) {
        if (i_func == sin)
            result += std::sin(low_limit + i * h);
        else if (i_func == cos)
            result += std::cos(low_limit + i * h);
        else if (i_func == exp)
            result += std::exp(low_limit + i * h);
    }
    intgr = result * h;
    return result * h;

}


// Метод правых прямоугльников
double Integral::Rightpoint()
{   intgr = 0;
    double h = (up_limit - low_limit) / n;
    double result = 0;
    for (int i = 0; i < n; i++) {
        if (i_func == sin)
            result += std::sin(low_limit + (i + 1) * h);
        else if (i_func == cos)
            result += std::cos(low_limit + (i + 1) * h);
        else if (i_func == exp)
            result += std::exp(low_limit + (i + 1) * h);
        
    }
    intgr = result * h;
    return result * h;

}

// Вывод значения интеграла
void Integral::Output(const char* name)
{
    cout << name << " intgrl = " << intgr << endl;
    //Тесты
    cout << name << "low_limit = " << low_limit << endl;
    cout << name << "up_limit = " << up_limit << endl;
    cout << name << "n = " << n << endl;
}

// Подсчёт и вывод  значения интеграла
void Integral::Results(const char* name)
{
    if (i_method == middle)
    {
        cout<< name <<": " << Midpoint() << endl;
    }
    else if (i_method == right)
    {
        cout<< name <<": " << Rightpoint() << endl;
    }
    else if (i_method == left)
    {
        cout<< name <<": " << Leftpoint() << endl;
    }
}


//Вывод виде таблицы
void Integral::Results_t() {
    cout << " Enter n: " << endl;
    cin >> n;
    cout << " Results for n " << n<< endl << endl;
    cout << "n\t\tLeft Rectangle\t\tDelta\t\tRight Rectangle\t\tDelta\t\tMiddle Rectangle\t\tDelta\n";
    cout << n << "\t" << Leftpoint()
        << "\t\t" << std::abs(actualValue - Leftpoint()) 
        << "\t\t" << Rightpoint() << "\t\t" << std::abs(actualValue - Rightpoint()) 
        << "\t\t" << Midpoint() << "\t\t" << std::abs(actualValue - Midpoint()) << "\n";
    }

// Деструктор
Integral:: ~Integral()
{
}


