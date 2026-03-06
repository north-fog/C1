#include <iostream>     //Библиотека ввода-вывода
#include <fstream>
#include "Vector_Sergeev.h" 

using namespace std;


void main()
{
	setlocale(LC_CTYPE, "Russian");


	Vector v1, v2, v3;
	int vCount = 5;

	int *d1 = new int[vCount];
	int *d2 = new int[vCount];
	int *d3 = new int[vCount];
	for ( int i = 0; i < vCount; ++i )  
	{
		d1[i] = 1 + (i + 1);
		d2[i] = 2 + (i + 1);
		d3[i] = 3 + (i + 1);
	}
	// инициализация векторов
	v1.Init(vCount, d1);
	v2.Init(vCount, d2);
	v3.Init(vCount, d3);

	v1.Output("v1");
	v2.Output("v2");
	v3.Output("v3");

	cout << "_________________________________________________________________" << endl;

	v1.Output_file("v1.txt");
	v2.Output_file("v2.txt");
	v3.Output_file("v3.txt");

	v1.Output("v1");
	v1 << "v1.txt";
	v1.Output("v1");

	cout << "_________________________________________________________________" << endl;

	
	cout << v1.Comp(4) << endl;
	
	cout << v1.Comp(5) << endl;
	
	cout << v1.Comp(6) << endl;

    cout << "_________________________________________________________________" << endl;
	Vector v4, v5;
	v4.Copy(v2);
	v5 = v3;
	v4.Output("v4");
	v5.Output("v5");

	cout << "_________________________________________________________________" << endl;

	Vector v6,v7;
	v6 = v1.Summ(v2);
	v7 = v2 + v3;;
	v6.Output("v6");
	v7.Output("v7");

	cout << "_________________________________________________________________" << endl;

	Vector v8,v9;
	v8 = v1.Mult(4);
	v9 = v2 * 4;
	v8.Output("v8");
	v9.Output("v9");

	cout << "_________________________________________________________________" << endl;

	int scal1 = v1.ScalMult(v2);
	int scal2 = v2 * v2;
	cout << "v1.scalMult(v3) = " << scal1 << endl;
	cout << "v2 * v3= " << scal2 << endl;

	cout << "_________________________________________________________________" << endl;

	Vector v10;
	v10 = v1;
	v10.Output("v10");
	cout << "_________________________________________________________________" << endl;
	Vector v11, v12;
	int *d11 = new int[10];
	for ( int i = 0; i < 10; ++i )  
	{
		d11[i]=1+i;
	}


	cout << "end" << endl;



}