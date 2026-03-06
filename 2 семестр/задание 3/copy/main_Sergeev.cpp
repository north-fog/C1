#include <iostream>     //Библиотека ввода-вывода
#include <fstream>
#include "Integral_Sergeev.h" 

using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Russian");
    
    Integral i1, i2 , i3;
    i1.Set_limit(0,10);
    i1.Set_div(100);
    i1.Set_func("sin");
    i1.Set_metod("left");
    i1.Results("i1");
    i2.Set_limit(0,10);
    i2.Set_div(100);
    i2.Set_func("cos");
    i2.Set_metod("right");
    i2.Results("i2");
    i3.Set_limit(0,10);
    i3.Set_div(100);
    i3.Set_func("exp");
    i3.Set_metod("middle");
    i3.Results("i3"); 
    i1.Results_t();  



    cout << "______________________________________" << endl;
}


