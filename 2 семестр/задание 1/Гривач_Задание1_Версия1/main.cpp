#include <cstdlib>
#include <iostream>
using namespace std;
#include "Rational.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
 Rational r1(7,3);
 Rational r2(1,3);
 Rational r3;
 Rational::setDebugLevel(1);
 cout << "r3 = " << r3 << endl;
 r3=r1;
 cout << "r3 (" << r3 << ") = r1 (" << r1 << ")" << endl;
 ++r3;
 cout << "++r3 = " << r3 << endl;
 r3++;
 cout << "r3++ = " << r3 << endl;
 r3+=r2;
 cout << "r3+=r2 = " << r3 << " (r2= " << r2 << ")" << endl;
 r3=-r2;
 cout << "r3 = -r2 = " << r3 << endl;

 r3=r1+r2;
 cout << r1 << " + " << r2 << " = " << r3 << endl;
 r3=r1-r2;
 cout << r1 << " - " << r2 << " = " << r3 << endl;
 r3=r1*r2;
 cout << r1 << " * " << r2 << " = " << r3 << endl;
 r3=r1/r2;
 cout << r1 << " / " << r2 << " = " << r3 << endl;

 cout << r1 << " is:" << endl;
 if(r1 < r2)cout << " < " << r2 << endl;
 else cout << " not < " << r2 << endl;

 if(r1 <= r2)cout << " <= " << r2 << endl;
 else cout << " not <= " << r2 < r2)cout < " << r2 << endl;
 else cout < " << r2 <= r2)cout <= " << r2 << endl;
 else cout <= " << r2 << endl;

 if(r1 == r2)cout << " == " << r2 << endl;
 else cout << " not == " << r2 << endl;

 if(r1 != r2)cout << " != " << r2 << endl;
 else cout << " not != " << r2 << endl;

 cout << "Общее количество вызванных конструкторов: " << Rational::getCount() << endl;

 system("PAUSE");
 return EXIT_SUCCESS;
}