#include <iostream>     //Библиотека ввода-вывода
#include <cmath>        //Библиотека основных мат. функций

using namespace std;

class Rational
{
    public:
    Rational();                         // Конструктор по умолчанию
	Rational(const Rational &c);        // Конструктор копирования
	Rational(int _num, int _den);       // Конструктор инициализации
	Rational(double d);                 // Конструктор преобразования типа
	~Rational();                        // Деструктор

    int GCD(int a, int b);              //Конструктор поиска НОД
    
    // Перегрузка операций ----------------------
	void operator=(const Rational& c);
    Rational operator+(const Rational& c);
    Rational operator+(double d);
    Rational operator-(const Rational& c);
    Rational operator-(double d);
    Rational operator*(const Rational& c);
    Rational operator/(const Rational& c);
    
	bool operator==(const Rational& c);
    friend ostream& operator<<(ostream& stream, const Rational& c); 
    friend istream& operator>>(istream& stream, Rational& c);

    private:
        int num;
        int den;
};

// Поиск НОД
int Rational::GCD(int a, int b)
{
    a=abs(a),b=abs(b);
    if (b == 0)return a;
    else return GCD(b, a%b);
}

// Конструктор по умолчанию
Rational::Rational()
{
	num = 0;  	den = 1;
}

// Конструктор копирования
Rational::Rational(const Rational& c) 
{
	num = c.num;  den = c.den;
}

// Конструктор инициализации
Rational::Rational(int _num, int _den)
{
	if (_den == 0)
    {
        cout << "Знаменатель не может быть равен нулю " << endl;
        _den = 1;
    } 
    int x=GCD(_num,_den);   //Сокращение дроби
    num = _num/x;   den = _den/x;
}

// Конструктор преобразования типа
Rational::Rational(double d)
{
    double  _dnum = d;
    int i=0;
    while (_dnum-int(_dnum) !=0.0) _dnum*=10, i++;  //Преобразование в десятичную дробь
    int _num = int(_dnum);
    int _den =  pow(10,i);
    if(_num==0)
    {
        num = 0;   den = 1;
    }
    else
    {
        int x=GCD(_num,_den);   //Сокращение дроби
        num = _num/x;   den = _den/x;
    }
}

// Деструктор
Rational::~Rational()
{
	num = 0; 	den = 0;
}

//Перегрузка присваивания
void Rational::operator=(const Rational& c) 
{
	num = c.num;    den = c.den;
}

//Перегрузка сложения
Rational Rational::operator+(const Rational& c)
{
	Rational res;
	res.num = num * c.den + den * c.num;
	res.den = den * c.den;
    int x=GCD(res.num,res.den);
    res.num/=x;     res.den/=x;
	return res;
}
//Перегрузка сложения
Rational Rational::operator+(double d)
{
     Rational res;
    if (d == 0)
    {
        res.num = num;
	    res.den = den; 
    }
    else
    {
        Rational t(d);
        res.num = num * t.den + den * t.num;
        res.den = den * t.den;
        int x=GCD(res.num,res.den);
        res.num/=x;     res.den/=x;
    }
	return res;
}

//Перегрузка вычитания
Rational Rational::operator-(const Rational& c)
{
	Rational res;
	res.num = num * c.den - den * c.num;
	res.den = den * c.den;
    int x=GCD(res.num,res.den);
    res.num/=x;     res.den/=x;
	return res;
}

//Перегрузка вычитания
Rational Rational::operator-(double d)
{
    Rational res;
    if (d == 0)
    {
        res.num = num;
	    res.den = den; 
    }
    else
    {
        Rational t(d);
        res.num = num * t.den - den * t.num;
        res.den = den * t.den;
        int x=GCD(res.num,res.den);
        res.num/=x;     res.den/=x;
    }
    return res;
}
//Перегрузка умножения
Rational Rational::operator*(const Rational& c)
{
    Rational res;
    res.num = num * c.num;
    res.den = den * c.den;
    int x=GCD(res.num,res.den);
    res.num/=x;     res.den/=x;
    return res;
}
//Перегрузка деления
Rational Rational::operator/(const Rational& c)
{
    Rational res;
    res.num = num * c.den;
    res.den = den * c.num;
    int x=GCD(res.num,res.den);
    res.num/=x;     res.den/=x;
    return res;
}

//Перегрузка сравнения
bool Rational::operator==(const Rational& c)
{
	bool res;
	res = (num == c.num) && (den == c.den);
	return res;
}
//Перегрузка Вывода
ostream& operator<<(ostream& stream, const Rational& c)  
{
	stream << c.num << "/" << c.den << endl;
	return stream;
}
//Перегрузка ввода
istream& operator>>(istream& stream, Rational& c) 
{
    int _num, _den;
	stream >> _num >> _den; 
	return stream;
}

void main()
{
    setlocale(LC_ALL, "rus");   //Локализация

    Rational r0;                // По умолчанию
	Rational r1(1, 2);          // Инициализатор
	Rational r2(3, 4);          // Инициализатор
	Rational r3(r1);            // Копирования
	Rational r4(0);             // Преобразования 

    cout << r0;
    cout << r1;
    cout << r2;
    cout << r3;
    cout << r4;

    cout << "_________________________________________________________________" << endl;
    r0 =  r4;
    cout << r0;
    cout << (r0 == r4) << endl;
    cout << (r0 == r3) << endl;
    cout << (r2 + r4);
    cout << (r2 + 0.0);
    cout << (r2 + 1);
    cout << "_________________________________________________________________" << endl;
    cout << (r2 * r3);
    cout << (r2 / r3);
}