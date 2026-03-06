// Файл Complex.h ---------------------------------------
#pragma once

class Complex {
public:
	// инициализация объекта класса
	void init(double _re, double _im);

	void SRe(double _re) { re = _re;  } 
	double Re()          { return re; } 
	void SIm(double _im) { im = _im;  } 
	double Im()          { return im; }

	void inPut();
	void outPut(const char* name);
	Complex add(const Complex& c);
	Complex sub(const Complex& c);
	Complex mul(const Complex& c);
	bool equ(const Complex& c);
private:
	double re; // действительная часть
	double im; // мнимая часть
};
