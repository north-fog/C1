// Τΰιλ Complex.cpp ---------------------------------------
#include <iostream>
using namespace std;

#include "Complex.h"

void Complex::init(double _re, double _im) {
	re = _re;
	im = _im;
}

void Complex::inPut() {
	cout << "re = ";
	cin >> re;
	cout << "im = ";
	cin >> im;
}
void Complex::outPut(const char* name) {
	cout << name << ": re = " << re << ": im = " << im << endl;
}
Complex Complex::add(const Complex& c) {
	Complex res;
	res.re = re + c.re;
	res.im = im + c.im;
	return res;
}
Complex Complex::sub(const Complex& c) {
	Complex res;
	res.init(re - c.re, im - c.im);
	return res;
}
Complex Complex::mul(const Complex& c) {
	Complex res;
	res.re = re * c.re - im * c.im;
	res.im = re * c.im + im * c.re;
	return res;
}

bool Complex::equ(const Complex& c) {
	return re == c.re && im == c.im;
}
