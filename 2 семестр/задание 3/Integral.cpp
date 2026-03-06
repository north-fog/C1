#include <iostream>     //Библиотека ввода-вывода
#include <fstream>		//Библиотека ввода-вывода
#include "Integral.h" 	//Заголовочный файл вектора
#include <cmath> 
// #include <functional>
using namespace std;



// Конструдтор по умолчанию
Integral::Integral()
{

}

// Конструтор создания 
Integral::Integral(int _low_limit, int _up_limit,int _n, int _s_fun)
{
    low_limit = _low_limit;
    up_limit = _up_limit;
    n = _n;
    s_fun =  _s_fun;

}

// Конструтор иницилизации
void Integral::Init(double _low_limit, double _up_limit,double _n, int _s_fun)
{
    low_limit = _low_limit;
    up_limit = _up_limit;
    n = _n; 
    s_fun =  _s_fun;


}
void Integral::Set_limit(int a, int b)
{
    low_limit = a;
    up_limit = b;
}
void Integral::Set_div(int div)
{
    n = div;
}
void Integral::Set_func(int f)
{

}

void Integral::Set_metod(int m)
{

}







// Метод средних прямоугльников
double Integral::Midpoint()
{   intgr = 0;
    double h = (up_limit - low_limit) / n;
    double result = 0;
    for (int i = 0; i < n; i++) 
    {
        if (s_fun==1)
            result += fsin(low_limit + (i + 0.5) * h);
        else if (s_fun == 2)
            result += fcos(low_limit + (i + 0.5) * h);
        else
            result += fexp(low_limit + (i + 0.5) * h);

        
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
        if (s_fun==1)
            result += fsin(low_limit + i * h);
        else if (s_fun == 2)
            result += fcos(low_limit + i * h);
        else
            result += fexp(low_limit + i * h);
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
        if (s_fun==1)
            result += fsin(low_limit + (i + 1) * h);
        else if (s_fun == 2)
            result += fcos(low_limit + (i + 1) * h);
        else
            result += fexp(low_limit + (i + 1) * h);
        
    }
    intgr = result * h;
    return result * h;

}

// // Синус
// double Integral::fsin(double x)
// {
//     return sin (x);
// }

// // Косинус
// double Integral::fcos(double x)
// {
//     return cos (x);
// }

// // Экспонента
// double Integral::fexp(double x)
// {
//     return exp (x);
// }

// Вывод значения интеграла
void Integral::Output(const char* name)
{
    cout << name << " intgrl = " << intgr << endl;
    //Тесты
    cout << name << "low_limit = " << low_limit << endl;
    cout << name << "up_limit = " << up_limit << endl;
    cout << name << "n = " << n << endl;
}

// Вывод виде таблицы
void Integral::Results() {
    cout << " Enter n: " << endl;
    cin >> n;
    cout << " Results for n " << n << endl << endl;
    cout << "n\tLeft Rectangle\tDelta\tRight Rectangle\tDelta\tMiddle Rectangle\tDelta\n";
    cout << n << "\t" << Leftpoint() << "\t"  << "\t" <<Rightpoint() << "\t"  << "\t" << Midpoint() << "\t" << "\n";
}

// Деструктор
Integral:: ~Integral()
{
    n = 0;
    low_limit = 0;
    up_limit = 0;
    intgr = 0;
}


