#include <cstdlib>
#include <iostream>
using namespace std;
#include "Rational.h"

int Rational::debug=0;
int Rational::count=0;

ostream& operator<<(ostream& outs,
 const Rational& toPrint)
{
 toPrint.print(outs);
 return outs;
}

Rational::Rational(int n, int d)
{
 if(getDebug()>0)
 cout << "Конструктор Rational по умолчанию, вызываемый с помощью num = "
 << n << " den = " << d << endl;
 Rational::incrementCount();
 num=n;
 den=d;
 reduce();
}
Rational::Rational(const Rational& copy )
{
 if(getDebug()>0)
 cout << "Конструктор Rational copy, вызываемый с помощью num = "
 << copy.num << " den = " << copy.den << endl;
 Rational::incrementCount();
 num=copy.num;
 den=copy.den;
 reduce();
}
const Rational& Rational::operator=(const Rational& rhs)
{
 if(getDebug()>0)
 cout << "Оператор рационального присваивания, вызываемый с помощью num = "
 << rhs.num << " den = " << rhs.den << endl;
 if(&rhs != this) {
 num=rhs.num;
 den=rhs.den;
 reduce();
 }
}
const Rational& Rational::operator+=(const Rational& rhs)
{
 long tnum,tden;
 tnum=num;
 tden=den;
 if(getDebug()>0)
 cout << "Рациональный оператор объединения, вызываемый с помощью num = "
 << rhs.num << " den = " << rhs.den << endl;
 num=tnum*rhs.den+tden*rhs.num;
 den=tden*rhs.den;
 reduce();
}
Rational& Rational::operator++()
{
 if(getDebug()>0)
 cout << "Оператор рационального приращения префикса, вызываемый с помощью num = "
 << num << " den = " << den << endl;
 num+=den;
 return *this;
}
Rational Rational::operator++(int)
{
 if(getDebug()>0)
 cout << "Рациональный оператор постфиксного приращения, вызываемый с помощью num = "
 << num << " den = " << den << endl;
 Rational temp(num,den);
 num+=den;
 return temp;
}
Rational Rational::operator-()
{
 return Rational(-num,den);
}
Rational Rational::operator+(Rational& rhs)
{
 return Rational(num*rhs.den+den*rhs.num,den*rhs.den);
}
Rational Rational::operator-(Rational& rhs)
{
 return Rational(num*rhs.den-den*rhs.num,den*rhs.den);
}
Rational Rational::operator*(Rational& rhs)
{
 return Rational(num*rhs.num,den*rhs.den);
}
Rational Rational::operator/(Rational& rhs)
{
 return Rational(num*rhs.den,den*rhs.num);
}
bool Rational::operator<(const Rational& rhs) const
{
    return (num*rhs.den)<(den*rhs.num);
}
bool Rational::operator==(const Rational& rhs) const
{
 return (num*rhs.den)==(den*rhs.num);
}
void Rational::print(ostream& outs) const
{
 if(den==1)
 cout << num;
 else
 cout << num << "/" < den;
}
void Rational::reduce()
{
 long loop, largest, gcd=1;
 largest=(num > den)) ? num : den;
 for(loop=2; loop <= largest; loop++ )
 {
 if(num%loop == 0L && den%loop == 0L)gcd=loop;
 }
 num/=gcd;
 den/=gcd;
}