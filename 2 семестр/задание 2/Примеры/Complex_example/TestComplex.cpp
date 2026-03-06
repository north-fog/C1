// Τΰιλ TestComplex.cpp ---------------------------------------
#include <iostream>
//#include <fstream>
#include <clocale>
using namespace std; 

#include "Complex.h"


//std::ofstream cout("rezult.txt", std::ios::out);

int main()
{
	setlocale(LC_CTYPE, "Russian");

	Complex c1, c2, c3;
	c1.init(1.1, 2.2);
	c2.SRe(3.3);
	c2.SIm(4.4);
	c3.inPut();
	c1.outPut("c1");
	c2.outPut("c3");
	c3.outPut("c3");
	c1 = c2.add(c3);
	c1.outPut("c1");
	c1 = c2.sub(c3);
	c1.outPut("c1");
	c1 = c2.mul(c3);
	c1.outPut("c1");
	cout << "c2.equ(c3) = " << c2.equ(c3) << endl;
	c1 = c3;
	cout << "c1.equ(c3) = " << c1.equ(c3) << endl;

	return 0;
}

