// Файл TestVector.cpp ---------------------------------------
#include <iostream>
//#include <fstream>
#include <clocale>
#include <iomanip>
using namespace std; 

#include "Vector.h"

//std::ofstream cout("rezult.txt", std::ios::out);

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
	// инициализация векторов
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

	v3 = v2;
	v3.outPut("v3");

	Vector v6; v6.create(3);
	v6.Assign(v2);
	v6.outPut("v6");

	Vector v4; v4.create(vCount);
	v4.Assign(v1.Summ(v2));
	v4.outPut("v4");

	Vector v5; v5.create(vCount);
	v5.Assign(v1.doubMult(1.1));
	v5.outPut("v5");

	double scal = v1.scalMult(v2);
	cout << "v1.scalMult(v2) = " << scal << endl;
	
	// деинициализация векторов	
	v1.deInit();
	v2.deInit();
	v3.deInit();
	v4.deInit();
	v5.deInit();
	v6.deInit();

	return 0;
}

