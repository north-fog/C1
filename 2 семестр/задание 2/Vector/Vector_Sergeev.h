// Файл Vector.h ---------------------------------------
#pragma once

class Vector {
public:	
    Vector();											// коннструтор по умолчанию
	Vector(int _len, double* d);						// коннструтор создания 
	Vector(int _len, int* d);							// коннструтор создания 
	void Init(int _len, int* d);						// коннструтор Инициализации 
	void Create(int _len);								// Создание "пустого" вектора
	int Comp(int index);								// Доступ к компонентам по индексу (чтение и запись)
	void Copy(const Vector &vec);						// Копирование
	void Assign(const Vector &vec);						// Присваивание вектора
	void Output(const char* name);						// Вывод на консоль
	void Output_file(const char* file_name);			// Запись вектора в файл
	void Input_file(const char* file_name);				// Запись вектора из файла
	Vector Summ(const Vector &vec);						// Суммирование векторов
	int ScalMult(const Vector &vec);					// Скалярное произведение векторов
	Vector Mult(int d); 								// Умножение действительного на вектор
	Vector operator+(const Vector &vec);				// Перегрузка операции +
	Vector operator*(int d);							// Перегрузка операции * для умножения действительного на вектор
	int operator*(const Vector &vec);					// Перегрузка операции * для скалярного произведение векторов
	void operator>>(const char* file_name);				// Перегрузка операции >>
	void operator<<(const char* file_name);				// Перегрузка операции <<
	void operator=(const Vector &vec);					//
	~Vector();											// Дестркутор

private:
	int *dim;											// Массив компонент вектора
	int len;    										// Количество компонент вектора


	enum ErrorTypes{Vecdifflens, Outofrange};
	struct Vecexp
	{
		ErrorTypes misstype;
		int index;
		Vecexp(ErrorTypes _missstype, int _index):
		misstype(_missstype), index(_index){}
	};
	
};
