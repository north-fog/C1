// ‘айл Vector.h ---------------------------------------
#pragma once

class Vector {
public:
	// инициализаци€ объекта класса
	void init(int _count, double* d);
	// создание "пустого"вектора
	void create(int _count);
	// деинициализаци€ объекта класса
	void deInit();
	// доступ к компонентам по индексу (чтение и запись)
	double& Comp(int index);
	// вывод на консоль
	void outPut(const char* name);
	// присваивание вектора
	void Assign(const Vector &vec);
	// суммирование векторов
	Vector Summ(const Vector &vec);
	// скал€рное произведение векторов
	double scalMult(const Vector &vec);
	// умножение действительного на вектор
	Vector doubMult(double d); 
	Vector::Vector(int _len);
private:
	double *memo; // массив компонент вектора
	int count;    // количество компонент вектора
};
