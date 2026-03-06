// ‘айл Vector.cpp ---------------------------------------
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
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
	cout << name << ": ";
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
int main()
{
	setlocale(LC_CTYPE, "Russian");

	Vector v1, v2, v3;
	int vCount = 5;
	double *d1 = new double[vCount];
	double *d2 = new double[vCount];
	double *d3 = new double[vCount];
	for ( int i = 0; i < vCount; ++i )  {
		d1[i] = 1 + (i + 1)*0.1;
		d2[i] = 2 + (i + 1)*0.1;
		d3[i] = 3 + (i + 1)*0.1;
	}
	// инициализаци€ векторов
	v1.init(vCount, d1);
	v2.init(vCount, d2);
	v3.init(vCount, d3);

	// задание точности и формата вывода
	cout << setprecision( 2 ) << fixed;

	v1.outPut("v1");
	v2.outPut("v2");
	v3.outPut("v3");

	double comp = v1.Comp(2);
	cout << "v1.Comp(2) = " << comp << endl;
	v1.Comp(3) = 4.4;
	v1.outPut("v1");

	v3.Assign(v2);
	v3.outPut("v3");

	Vector v4; v4.create(vCount);
	v4.Assign(v1.Summ(v2));
	v4.outPut("v4");

	Vector v5; v5.create(vCount);
	v5.Assign(v1.doubMult(1.1));
	v5.outPut("v5");

	double scal = v1.scalMult(v2);
	cout << "v1.scalMult(v2) = " << scal << endl;
	
	// деинициализаци€ векторов	
	v1.deInit();
	v2.deInit();
	v3.deInit();
	v4.deInit();
	v5.deInit();

	return 0;
}
