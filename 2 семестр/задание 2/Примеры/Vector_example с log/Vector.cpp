// ‘айл Vector.cpp ---------------------------------------
#include <iostream>
using namespace std;

#include "Vector.h"

// инициализаци€ объекта класса
void Vector::init(int _count, double* d)  {
	count = _count;
	memo = new double[count];
	for ( int i = 0; i < count; ++i )
		memo[i] = d[i];
}
// создание объекта класса
void Vector::create(int _count)  {
	count = _count;
	memo = new double[count];
}

// деинициализаци€ объекта класса
void Vector::deInit()  {
	cout << "deInit: " << hex << this << ":"  << memo << memo << endl;   
	if ( memo != NULL ) {
		delete[] memo;
		memo = NULL;
		count = 0;
	}
}

// доступ к компонентам по индексу (чтение и запись)
double& Vector::Comp(int index)  {
	if ( index < 0 || index >= count )
		abort(); // принудительное завершение программы
	return memo[index];
}

// вывод на консоль
void Vector::outPut(const char* name)  {
	//cout << name << ": ";
	cout << name << ": " << hex << this << ":"  << memo << " = ";
	for ( int i = 0; i < count; ++i )
		cout << memo[i] << ",\t";
	cout << endl;
}

// присваивание вектора
void Vector::Assign(const Vector &vec){
	if ( this != &vec ) { // не надо присваивать себ€ себе!
		if ( count != vec.count )
		{
			delete[] memo;
			count = vec.count;
			memo = new double[count];
		}
		for ( int i = 0; i < count; ++i )
			memo[i] =  vec.memo[i];
	}
}

// суммирование векторов
Vector Vector::Summ(const Vector &vec)  {
	if ( count != vec.count )
		abort(); // принудительное завершение программы
	Vector res;
	res.create(count);
	for ( int i = 0; i < count; ++i )
		res.memo[i] = memo[i] + vec.memo[i];
	return res;
}
// скал€рное произведение векторов
double Vector::scalMult(const Vector &vec)  {
	if ( count != vec.count )
		abort(); // принудительное завершение программы
	double res = 0.0;
	for ( int i = 0; i < count; ++i )
		res += memo[i] * vec.memo[i];
	return res;	
}
// умножение действительного на вектор
Vector Vector::doubMult(double d)  {
	Vector res;
	res.create(count);
	for ( int i = 0; i < count; ++i )
		res.memo[i] = d * memo[i];
	return res;	
}

