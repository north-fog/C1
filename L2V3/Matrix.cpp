#include "Matrix.h"
#include <cmath>


template <class ValType>
TMatrix<ValType>::TMatrix(int s) 
    : TVector<TVector<ValType> >(s) {
    for (int i = 0; i < s; i++) {
        this->pVector[i] = TVector<ValType>(s - i, i);
    }
}

// Конструктор копирования
template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt)
    : TVector<TVector<ValType> >(mt) {}

// Конструктор преобразования 
template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt)
    : TVector<TVector<ValType> >(mt) {
}

// Оператор сравнения матриц
template <class ValType>
int TMatrix<ValType>::operator==(const TMatrix& mt)  {
    return TVector<TVector<ValType> >::operator==(mt);
}

// Оператор присваивания
template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    if (this != &mt) {
        TVector<TVector<ValType> >::operator=(mt);
    }
    return *this;
}


template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt)  {
    if (this->GetSize() != mt.GetSize()) {
        throw "Ошибка: матрицы разного размера!";
    }
    
    TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator+(mt);
    
    return TMatrix(result);
}

// Вычитание матриц
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt)  {
    if (this->GetSize() != mt.GetSize()) {
        throw "Ошибка: матрицы разного размера!";
    }
    
    TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator-(mt);
    
    return TMatrix(result);
}

// Умножение матриц:
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& mt)  {
    int n = this->GetSize();
    
    if (n != mt.GetSize()) {
        throw "Ошибка: матрицы разного размера!";
    }
    
    TMatrix<ValType> result(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ValType sum = 0;
            for (int k = i; k <= j; k++) {
                sum += (*this)(i, k) * mt(k, j);
            }
            result(i, j) = sum;
        }
    }
    
    return result;
}

// Умножение матрицы на вектор
template <class ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& v)  {
    int n = this->GetSize();
    
    if (n != v.GetSize()) {
        throw "Ошибка: размер матрицы и вектора не совпадают!";
    }
    
    TVector<ValType> result(n);
    
    for (int i = 0; i < n; i++) {
        ValType sum = 0;
        for (int j = i; j < n; j++) {
            sum += (*this)(i, j) * v[j];
        }
        result[i] = sum;
    }
    
    return result;
}

// Доступ к элементу матрицы по индексам 
template <class ValType>
ValType& TMatrix<ValType>::operator()(int i, int j) {
    if (i < 0 || i >= this->GetSize() || j < 0 || j >= this->GetSize()) {
        throw "Ошибка: индексы вне диапазона!";
    }
    
    if (j < i) {
        throw "Ошибка: попытка доступа к нулевому элементу (ниже диагонали)!";
    }
    return this->pVector[i][j - i];
}
template <class ValType>
ValType TMatrix<ValType>::operator()(int i, int j)const {
    if (i < 0 || i >= this->GetSize() || j < 0 || j >= this->GetSize()) {
        throw "Ошибка: индексы вне диапазона!";
    }
    
    if (j < i) {
        return 0;  // элементы ниже диагонали равны 0
    }
    
    return this->pVector[i][j - i];
}

template class TMatrix<int>;
template class TMatrix<double>;