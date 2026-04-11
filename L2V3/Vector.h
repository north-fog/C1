#pragma once
#include <iostream>
using namespace std;

template <class ValType>
class TVector {
protected:
    ValType* pVector;   // указатель на динамический массив элементов
    int Size;           // размер вектора (количество элементов)
    int StartIndex;     // индекс первого элемента (для совместимости)

public:
    // Конструкторы
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);
    ~TVector();
    
    // Методы доступа
    int GetSize() const { return Size; }
    int GetStartIndex() const { return StartIndex; }
    ValType& GetValue(int pos);
    ValType& operator[](int pos);
    
    // Сравнение
    int operator==(const TVector& v) const;
    
    // Присваивание
    TVector& operator=(const TVector& v);
    
    // Скалярные операции
    TVector operator+(const ValType& val) const;
    TVector operator-(const ValType& val) const;
    TVector operator*(const ValType& val) const;
    
    // Векторные операции
    TVector operator+(const TVector& v) const;
    TVector operator-(const TVector& v) const;
    ValType operator*(const TVector& v) const;  // скалярное произведение
    
    // Вычисление длины
    ValType Length() const;
    
    // Ввод/вывод
    friend istream& operator>>(istream& in, TVector& v) {
        for (int i = 0; i < v.Size; i++) {
            in >> v.pVector[i];
        }
        return in;
    }
    
    friend ostream& operator<<(ostream& out, const TVector& v) {
        out << "( ";
        for (int i = 0; i < v.Size; i++) {
            out << v.pVector[i];
            if (i < v.Size - 1) out << ", ";
        }
        out << " )";
        return out;
    }
};