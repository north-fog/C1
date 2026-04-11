#pragma once
#include "Vector.h"


template <class ValType>
class TMatrix : public TVector<TVector<ValType> > {
public:

    TMatrix(int s = 10);
    
    // Конструктор копирования
    TMatrix(const TMatrix& mt);
 
    // Конструктор преобразования из вектора векторов
    TMatrix(const TVector<TVector<ValType> >& mt);
    
    // Сравнение матриц
    int operator==(const TMatrix& mt) const;
    
    // Присваивание
    TMatrix& operator=(const TMatrix& mt);
    
    // Сложение матриц
    TMatrix operator+(const TMatrix& mt) const;
    
    // Вычитание матриц
    TMatrix operator-(const TMatrix& mt) const;
    
    // Умножение матриц
    TMatrix operator*(const TMatrix& mt) const;
    
    // Умножение матрицы на вектор
    TVector<ValType> operator*(const TVector<ValType>& v) const;
    
    // Доступ к элементу матрицы по индексам 
    ValType& operator()(int i, int j);
    ValType operator()(int i, int j) const;
    
    // Получить размер матрицы
    int GetSize() const { return TVector<TVector<ValType> >::GetSize(); }
    
    // Ввод/вывод
    friend istream& operator>>(istream& in, TMatrix& mt) {
        int n = mt.GetSize();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {  // только верхний треугольник
                in >> mt(i, j);
            }
        }
        return in;
    }
    
    friend ostream& operator<<(ostream& out, const TMatrix& mt) {
        int n = mt.GetSize();
        out << "Матрица " << n << "x" << n << ":" << endl;
        for (int i = 0; i < n; i++) {
            out << "[ ";
            for (int j = 0; j < n; j++) {
                if (j < i) {
                    out << "0\t";  // ниже диагонали — 0
                } else {
                    out << mt(i, j) << "\t";
                }
            }
            out << "]" << endl;
        }
        return out;
    }
};