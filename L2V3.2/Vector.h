#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <class ValType>
class TVector {
protected:
    ValType* pVector;
    int Size;
    int StartIndex;

public:
    TVector(int s = 10, int si = 0) : Size(s), StartIndex(si) {
        pVector = new ValType[Size]();
    }
    
    TVector(const TVector& v) {
        Size = v.Size;
        StartIndex = v.StartIndex;
        pVector = new ValType[Size]();
        for (int i = 0; i < Size; i++) {
            pVector[i] = v.pVector[i];
        }
    }
    
    ~TVector() {
        delete[] pVector;
    }
    
    int GetSize() const { return Size; }
    int GetStartIndex() const { return StartIndex; }
    
    ValType& GetValue(int pos) {
        if (pos < 0 || pos >= Size) {
            throw "Ошибка: индекс вне диапазона!";
        }
        return pVector[pos];
    }
    
    ValType& operator[](int pos) {
        return GetValue(pos);
    }
    
    const ValType& operator[](int pos) const {
        if (pos < 0 || pos >= Size) {
            throw "Ошибка: индекс вне диапазона!";
        }
        return pVector[pos];
    }
    
    int operator==(const TVector& v) const {
        if (Size != v.Size) return 0;
        for (int i = 0; i < Size; i++) {
            if (pVector[i] != v.pVector[i]) return 0;
        }
        return 1;
    }
    
    int operator!=(const TVector& v) const{
        return !(*this == v);
    }
    
    TVector& operator=(const TVector& v) {
        if (this != &v) {
            if (Size != v.Size) {
                delete[] pVector;
                Size = v.Size;
                pVector = new ValType[Size]();
            }
            StartIndex = v.StartIndex;
            for (int i = 0; i < Size; i++) {
                pVector[i] = v.pVector[i];
            }
        }
        return *this;
    }
    
    TVector operator+(const ValType& val) const {
        TVector result(Size, StartIndex);
        for (int i = 0; i < Size; i++) {
            result.pVector[i] = pVector[i] + val;
        }
        return result;
    }
    
    TVector operator-(const ValType& val) const {
        TVector result(Size, StartIndex);
        for (int i = 0; i < Size; i++) {
            result.pVector[i] = pVector[i] - val;
        }
        return result;
    }
    
    TVector operator*(const ValType& val) const {
        TVector result(Size, StartIndex);
        for (int i = 0; i < Size; i++) {
            result.pVector[i] = pVector[i] * val;
        }
        return result;
    }
    
    TVector operator+(const TVector& v) const {
        if (Size != v.Size) throw "Ошибка: векторы разного размера!";
        TVector result(Size, StartIndex);
        for (int i = 0; i < Size; i++) {
            result.pVector[i] = pVector[i] + v.pVector[i];
        }
        return result;
    }
    
    TVector operator-(const TVector& v) const {
        if (Size != v.Size) throw "Ошибка: векторы разного размера!";
        TVector result(Size, StartIndex);
        for (int i = 0; i < Size; i++) {
            result.pVector[i] = pVector[i] - v.pVector[i];
        }
        return result;
    }
    
    ValType operator*(const TVector& v) const {
        if (Size != v.Size) throw "Ошибка: векторы разного размера!";
        ValType sum = 0;
        for (int i = 0; i < Size; i++) {
            sum += pVector[i] * v.pVector[i];
        }
        return sum;
    }
    
    ValType Length() const {
        ValType sum = 0;
        for (int i = 0; i < Size; i++) {
            sum += pVector[i] * pVector[i];
        }
        return sqrt(sum);
    }
    
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