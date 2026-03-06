#include <iostream>     //Библиотека ввода-вывода
#include <fstream>		//Библиотека ввода-вывода
#include <cmath>        //Библиотека метематики
using namespace std;

#pragma once
class Integral {
public:	
    enum func {sin, cos, exp};                                          // Список функций
    enum method {left, right, middle};                                  // Список методов
    Integral();                                                         // Конструдтор по умолчанию
    ~Integral();                                                        // Деструктор
    double Midpoint();                                                  // Метод средних прямоугльников
    double Leftpoint();                                                 // Метод левых прямоугльников
    double Rightpoint();                                                // Метод правых прямоугльников
    void Results(const char* name);                                     // Подсчёт и вывод  значения интеграла
    void Output (const char* name);                                     // Вывод значения интеграла
    void Set_limit(int a, int b);                                       // Задача пределов интегрирования 
    void Set_div(int div);                                              // Задача кол-во разбиений
    void Set_func(const char* _func);                                   // Задача функции
    void Set_metod(const char* _method);                                // Задача метода интегрирования 
    void Results_t();
    void setActualValue(double value)
	{
        actualValue = value;
    }

private:
func i_func;                                                            //Выбраная функция
method i_method;                                                        //Метод интегрирования
double up_limit;                                                        //Верхний предел
double low_limit;                                                       //Нижний предел
double n;                                                               //Кол - во разбиение
double intgr;                                                           //Значение интеграла
double actualValue;
};