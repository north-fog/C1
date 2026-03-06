#include <iostream>     //Библиотека ввода-вывода
#include <fstream>
#include "Integral.h" 

using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Russian");
    
    Integral i1, i2;
    i1.Init(0,10,100,1);
    i1.Output("i1");
    i1.Midpoint();
    i1.Output("i1");
    i1.Midpoint();
    i1.Output("i1");
    cout << "______________________________________" << endl;
    i1.Leftpoint();
    i1.Output("i1");
    i2.Init(0,10,100,1);
    i2.Results();

    // cout << i1("sin", 1, 100, 20, "left")


}


