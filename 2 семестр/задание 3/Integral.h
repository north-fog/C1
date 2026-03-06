#pragma once
class Integral {
public:	

    Integral();                                                         // Конструдтор по умолчанию
    Integral(int low_limit, int up_limit,int n,int s_fun);              // задание интеграла 
    void Init(double _l_limit, double _r_limit,double _n,int s_fun);    // задание интеграла 
    ~Integral();                                                        // Деструктор
    double Midpoint();                                                  // Метод средних прямоугльников
    double Leftpoint();                                                 // Метод левых прямоугльников
    double Rightpoint();                                                // Метод правых прямоугльников
    double fsin(double x);                                              // Синус
    double fcos(double x);                                              // Косинус
    double fexp(double x);                                              // Экспонента
    void Results();                                                     // Вывод виде таблицы
    void Output (const char* name);                                     // Вывод значения интеграла

    void Set_limit(int a, int b);
    void Set_div(int div);
    void Set_func(int f);
    void Set_metod(int m);





private:
int s_fun;                              //Выбраная функция
double up_limit;                        //Верхний предел
double low_limit;                       //Нижний предел
double n;                               //Кол - во разбиение
double intgr;                           //Значение интеграла
};