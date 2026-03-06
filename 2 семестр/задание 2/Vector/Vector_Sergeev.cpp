#include <iostream>     //Библиотека ввода-вывода
#include <fstream>		//Библиотека ввода-вывода
#include "Vector_Sergeev.h" 	//Заголовочный файл вектора
using namespace std;

//Вектор по умолчанию
Vector::Vector()
{
	len=0;
}

//Создание вектора 
Vector::Vector(int _len, int* d)
{
	Init(_len, d);
}

//Создание вектора с преобразванием из double
Vector::Vector(int _len, double* _d)
{
	int* d = new int[_len];
	for ( int i = 0; i < _len; i++ )
		d[i] = int(_d[i]);
	Init(_len, d);
}

//Иницилизация вектора
void Vector::Init(int _len, int* d)
{
	len=_len;
	dim = new int[len];
	for ( int i = 0; i < len; ++i )
		dim[i] = d[i];
}

//Создание вектора
void Vector::Create(int _len)
{
	len = _len;
	dim = new int[len];
}

//Дестркутор
Vector:: ~Vector()
{
	if ( dim != NULL )
	{
		if (len !=0)
		{	
			delete[] dim;
		}
		dim = NULL;
		len = 0;
	}
}


//Доступ к компонентам по индексу (чтение и запись)
int Vector::Comp(int index)  
{	
	try
	{
 		if ( index < 0 || index >= len ) 
		{
			int exeption = index;
       		throw Vecexp(Outofrange, index);
		} 
		else 
		{
			int i = dim[index];
			return i;
		}
	}

	catch (Vecexp& except)
	{
		cout << "Индекс находится за пределами размера вектора ";
	}
}



//Запись вектора из файла
void Vector::Input_file(const char* file_name)  
{
	ifstream in(file_name); // окрываем файл для чтения
    if (in.is_open())
    {
		in >>  len;
		dim = new int[len];
		int i=0;
        while (in >> dim[i]) i++;
    }
    in.close();     // закрываем файл
}

//Запись вектора в файл
void Vector::Output_file(const char* file_name)  
{
	ofstream out(file_name);
	if (out.is_open())
	{
		out << len << "\t";
		for ( int i = 0; i < len; i++ )
			out << dim[i] << "\t";
	}
}

//Вывод на консоль
void Vector::Output(const char* name)  
{
	cout << name <<": ";
	for ( int i = 0; i < len; i++ )
		cout << dim[i] << " ";
	cout << endl;
}

//Копирование вектора
void Vector::Copy(const Vector &vec)
{
	if ( this != &vec ) 
	{ 
		if ( len != vec.len )
		{
			if (len !=0)
			{
				delete[] dim;
			}
			len = vec.len;
			dim = new int[len];
		}
		 for ( int i = 0; i < len;i++ )
			dim[i] =  vec.dim[i];
	}
}

Vector Vector::Summ(const Vector &vec)  
{	

	Vector res;
	res.Create(len);
	for ( int i = 0; i < len;)
	{
		res.dim[i] = dim[i] + vec.dim[i];
		i++;
	}
	return res;
}
//Перегрузка операции +
Vector Vector::operator+(const Vector &vec)
{
	return Summ(vec);
}

//Умножение действительного на вектор
Vector Vector::Mult(int d)  
{
	Vector res;
	res.Create(len);
	for ( int i = 0; i < len; i++ )
		res.dim[i] = d * dim[i];
	return res;
}

//Перегрузка операции * для умножения действительного на вектор
Vector Vector::operator*(int d) 
{
	return Mult(d);
}

//Скалярное произведение векторов
int Vector::ScalMult(const Vector &vec)  
{
	int res = 0;
	for ( int i = 0; i < len; i++ )
		res += dim[i] * vec.dim[i];
	return res;	
}

//Перегрузка операции * для скалярного произведение векторов
int Vector::operator*(const Vector &vec)  
{
	return ScalMult(vec);
}

// Перегрузка операции >>
void Vector:: operator>>(const char* file_name)
{
	Output_file(file_name);
}

// Перегрузка операции <<
void Vector:: operator<<(const char* file_name)
{
	Input_file(file_name);
}
void Vector:: operator=(const Vector &vec)
{
	Copy(vec);
}