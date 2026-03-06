#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{
friend ostream& operator<<(ostream&, const Rational&);
friend istream& operator>>(istream&, Rational&);
private:
 static int debug; // отладка используется для того, чтобы отслеживать происходящее
 static int count; // count используется для подсчета количества экземпляров
public:
 Rational(int = 0, int = 1); // Конструктор по умолчанию
 Rational(const Rational& ); // Конструктор копирования
 Rational& operator++(); // Увеличение префикса
 const Rational& operator=(const Rational&); 
 const Rational& operator+=(const Rational&); 
 Rational operator++(int); // Постфиксное приращение
 Rational operator+(Rational&); //  сложение
 Rational operator-(Rational&); //  вычитание
 Rational operator*(Rational&); //  умножение
 Rational operator/(Rational&); //  деление
 Rational operator-(); // отрицание
 bool operator<(const Rational&) const;
 bool operator==(const Rational&) const;
 bool operator!=(const Rational& rhs) const
 { return !(*this == rhs); }
 bool operator>(const Rational&) const
 { return rhs < *this; }
 bool operator<=(const Rational& rhs) const
 { return !(rhs < *this); }
 bool operator>=(const Rational& rhs) const
 { return !(*this < rhs); }
 void print(ostream&) const; 
 void reduce(); // Уменьшить знаменатель
 static void setDebugLevel(int level) { debug=level; }
 static int getDebug() { return debug; }
 static void incrementCount() { count++; }
 static int getCount() { return count; }
protected:
 long num;
 long den;
};
#endif