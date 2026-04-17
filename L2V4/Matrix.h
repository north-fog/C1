#pragma once
#include "Vector.h"

template <class ValType>
class TMatrix : public TVector<TVector<ValType>> {
public:
    // Конструктор
    TMatrix(int s = 10) : TVector<TVector<ValType>>(s) {
        for (int i = 0; i < s; i++) {
            this->pVector[i] = TVector<ValType>(s - i, i);
        }
    }


    //std::

    
    // Конструктор копирования
    TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}
    
    // Конструктор преобразования
    TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}
    
    // Сравнение
    int operator==(const TMatrix& mt) const {
        return TVector<TVector<ValType>>::operator==(mt);
    }
    
    // Присваивание
    TMatrix& operator=(const TMatrix& mt) {
        if (this != &mt) {
            TVector<TVector<ValType>>::operator=(mt);
        }
        return *this;
    }
    
    // Сложение
    TMatrix operator+(const TMatrix& mt) const {
        if (this->GetSize() != mt.GetSize()) throw "Ошибка: матрицы разного размера!";
        TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator+(mt);
        return TMatrix(result);
    }
    
    // Вычитание
    TMatrix operator-(const TMatrix& mt) const {
        if (this->GetSize() != mt.GetSize()) throw "Ошибка: матрицы разного размера!";
        TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator-(mt);
        return TMatrix(result);
    }
    
    // Умножение матриц
    TMatrix operator*(const TMatrix& mt) const {
        int n = this->GetSize();
        if (n != mt.GetSize()) throw "Ошибка: матрицы разного размера!";
        
        TMatrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                ValType sum = 0;                    //valtype sume= valtype{}
                for (int k = i; k <= j; k++) {
                    sum += (*this)(i, k) * mt(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
    
    // Умножение матрицы на вектор
    TVector<ValType> operator*(const TVector<ValType>& v) const {
        int n = this->GetSize();
        if (n != v.GetSize()) throw "Ошибка: размер матрицы и вектора не совпадают!";
        
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
    
    // Доступ к элементу (запись)
    ValType& operator()(int i, int j) {
        if (i < 0 || i >= this->GetSize() || j < 0 || j >= this->GetSize()) {
            throw "Ошибка: индексы вне диапазона!";
        }
        if (j < i) throw "Ошибка: попытка доступа к нулевому элементу!";
        return this->pVector[i][j - i];
    }
    
    // Доступ к элементу (чтение)
    ValType operator()(int i, int j) const {
        if (i < 0 || i >= this->GetSize() || j < 0 || j >= this->GetSize()) {
            throw "Ошибка: индексы вне диапазона!";
        }
        if (j < i) return 0;
        return this->pVector[i][j - i];
    }
    
    // Получить размер
   // int GetSize() const { return TVector<TVector<ValType>>::GetSize(); }
    
    // Ввод матрицы (только верхний треугольник)
    friend istream& operator>>(istream& in, TMatrix& mt) {
        int n = mt.GetSize();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                in >> mt(i, j);
            }
        }
        return in;
    }
    
    // Вывод матрицы
    friend ostream& operator<<(ostream& out, const TMatrix& mt) {
        int n = mt.GetSize();
        for (int i = 0; i < n; i++) {
            out << "[ ";
            for (int j = 0; j < n; j++) {
                if (j < i) {
                    out << "0\t";
                } else {
                    out << mt(i, j) << "\t";
                }
            }
            out << "]" << endl;
        }
        return out;
    }

};