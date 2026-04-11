#include "Vector.h"

// Конструктор
template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si) {
    pVector = new ValType[Size]();
}

// Конструктор копирования
template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size]();
    
    // Копируем все элементы
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
}

// Деструктор: освобождает выделенную память
template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
}

// Получить значение элемента с проверкой границ
template <class ValType>
ValType& TVector<ValType>::GetValue(int pos) {
    if (pos < 0 || pos >= Size) {
        throw "Ошибка: индекс вне диапазона!";
    }
    return pVector[pos];
}

// Оператор доступа по индексу 
template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    return GetValue(pos);
}

// Оператор сравнения
template <class ValType>
int TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size) return 0;  // разный размер — не равны
    
    for (int i = 0; i < Size; i++) {
        if (pVector[i] != v.pVector[i]) return 0;
    }
    return 1;  // все элементы совпадают
}

// Оператор присваивания: 
template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v) return *this;  // защита от самоприсваивания
    
    // Если размеры разные, перевыделяем память
    if (Size != v.Size) {
        delete[] pVector;
        Size = v.Size;
        pVector = new ValType[Size]();
    }
    
    StartIndex = v.StartIndex;
    
    // Копируем элементы
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
    
    return *this;
}

// Прибавление скаляра: 
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] + val;
    }
    return result;
}

// Вычитание скаляра: 
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] - val;
    }
    return result;
}

// Умножение на скаляр: каждый элемент умножается на val
template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] * val;
    }
    return result;
}

// Сложение векторов
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size) {
        throw "Ошибка: векторы разного размера!";
    }
    
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] + v.pVector[i];
    }
    return result;
}

// Вычитание векторов: 
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size) {
        throw "Ошибка: векторы разного размера!";
    }
    
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] - v.pVector[i];
    }
    return result;
}

// Скалярное произведение векторов
template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size) {
        throw "Ошибка: векторы разного размера!";
    }
    
    ValType result = 0;
    for (int i = 0; i < Size; i++) {
        result += pVector[i] * v.pVector[i];
    }
    return result;
}

// Длина вектора:
template <class ValType>
ValType TVector<ValType>::Length() const {
    ValType sum = 0;
    for (int i = 0; i < Size; i++) {
        sum += pVector[i] * pVector[i];
    }
    return sqrt(sum);
}



template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < 0 || pos >= Size) {
        throw "Ошибка: индекс вне диапазона!";
    }
    return pVector[pos];
}

// Явное создание экземпляров шаблона для int и double
template class TVector<int>;
template class TVector<double>;
// template class TVector<TVector<int>>;
// template class TVector<TVector<double>>;