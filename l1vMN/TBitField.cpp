#include "TBitField.h"
#include <iomanip>
#include <iostream>  
using namespace std;


int TBitField::GetMemIndex(const int n) const {
    return n >> 5;  
}
TELEM TBitField::GetMemMask(const int n) const {
    return 1 << (n & 31);  
}

// Конструктор: создает битовое поле длины len
TBitField::TBitField(const int len) : BitLen(len) {
    // Проверка на корректность длины
    if (len <= 0) {
        throw "Ошибка в конструкторе TBitField: длина должна быть положительной!";
    }
    
    // Вычисляем, сколько элементов TELEM нужно для хранения len бит
    // (len + 31) >> 5 - это округление вверх при делении на 32
    MemLen = (len + 31) >> 5;
    
    // Выделяем динамическую память под массив и инициализируем всё 0
    pMem = new TELEM[MemLen]();
    
    // Проверка, что память выделилась
    if (pMem == nullptr) {
        throw "Ошибка в конструкторе TBitField: не удалось выделить память!";
    }
}

// Конструктор копирования: создает копию битового поля bf
TBitField::TBitField(const TBitField& bf) {
    // Копируем параметры из исходного объекта
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    
    // Выделяем новую память такого же размера
    pMem = new TELEM[MemLen]();
    
    // Проверка, что память выделилась
    if (pMem == nullptr) {
        throw "Ошибка в конструкторе копирования TBitField: не удалось выделить память!";
    }
    
    // Копируем данные из исходного объекта в новый
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];  // Копируем каждый элемент массива
    }
}

// Деструктор: освобождает выделенную память
TBitField::~TBitField() {
    delete[] pMem;  // Освобождаем динамический массив
}

// Устанавливает бит n в 1
void TBitField::SetBit(const int n) {
    // Проверяем, что n находится в допустимых пределах
    if (n < 0) {
        throw "Ошибка в SetBit: индекс бита не может быть отрицательным!";
    }
    if (n >= BitLen) {
        throw "Ошибка в SetBit: индекс бита выходит за границы поля!";
    }
    
    // OR с маской устанавливает нужный бит в 1
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

// Устанавливает бит n в 0 (очищает)
void TBitField::ClrBit(const int n) {
    // Проверяем, что n находится в допустимых пределах
    if (n < 0) {
        throw "Ошибка в ClrBit: индекс бита не может быть отрицательным!";
    }
    if (n >= BitLen) {
        throw "Ошибка в ClrBit: индекс бита выходит за границы поля!";
    }
    
    // AND с инвертированной маской очищает нужный бит
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

// Возвращает значение бита n (1 или 0)
int TBitField::GetBit(const int n) const {
    // Проверяем, что n находится в допустимых пределах
    if (n < 0) {
        throw "Ошибка в GetBit: индекс бита не может быть отрицательным!";
    }
    if (n >= BitLen) {
        throw "Ошибка в GetBit: индекс бита выходит за границы поля!";
    }
    
    // AND с маской даст 0, если бит не установлен, и не 0, если установлен
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// Оператор присваивания: копирует битовое поле bf в текущий объект
TBitField& TBitField::operator=(const TBitField& bf) {
    // Проверка на самоприсваивание
    if (this == &bf) {
        cout << "Предупреждение в operator=: попытка самоприсваивания" << endl;
        return *this;
    }

    BitLen = bf.BitLen;
    
    // Если размер памяти разный, нужно перевыделить память
    if (MemLen != bf.MemLen) {
        MemLen = bf.MemLen;  // Запоминаем новый размер
        
        // Освобождаем старую память
        delete[] pMem;
        
        // Выделяем новую память
        pMem = new TELEM[MemLen]();
        
        // Проверка, что память выделилась
        if (pMem == nullptr) {
            throw "Ошибка в operator=: не удалось выделить память!";
        }
    }
    
    // Копируем данные
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];  // Копируем каждый элемент
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Оператор сравнения: проверяет равенство двух битовых полей
int TBitField::operator==(const TBitField& bf) {
    // Если разная длина - сразу не равны
    if (BitLen != bf.BitLen) { 
        return 0; 
    }
    
    // Сравниваем каждый элемент массива
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;  // Нашли отличие
        }
    }
    
    return 1;  // Поля равны
}

// Оператор И (побитовое И) для двух битовых полей
TBitField TBitField::operator&(const TBitField& bf) {
    // Берем минимальную длину (результат не может быть длиннее меньшего поля)
    int minLen = (BitLen < bf.BitLen) ? BitLen : bf.BitLen;
    
    // Создаем временный объект минимальной длины
    TBitField tmp(minLen);
    
    // Определяем, сколько элементов массива нужно обработать
    int minMem = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    
    // Применяем побитовое И к элементам массивов
    for (int i = 0; i < minMem; i++) {
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    }
    
    return tmp;  // Возвращаем результат
}

// Оператор ИЛИ (побитовое ИЛИ) для двух битовых полей
TBitField TBitField::operator|(const TBitField& bf) {
    // Берем максимальную длину (результат должен вместить все биты из обоих полей)
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    
    // Создаем временный объект максимальной длины
    TBitField tmp(maxLen);
    
    // Копируем данные из текущего объекта
    for (int i = 0; i < MemLen; i++) {
        tmp.pMem[i] = pMem[i];
    }
    
    // Применяем побитовое ИЛИ с элементами второго объекта
    for (int i = 0; i < bf.MemLen; i++) {
        tmp.pMem[i] |= bf.pMem[i];
    }
    
    return tmp;  // Возвращаем результат
}

// Оператор НЕ (побитовое отрицание) для битового поля
TBitField TBitField::operator~() {
    // Создаем объект такой же длины
    TBitField res(BitLen);
    
    // Применяем побитовое НЕ ко всем элементам
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];  // Инвертируем все 32 бита в элементе
    }
    
    // Если длина не кратна 32, нужно обнулить лишние биты в последнем элементе
    if (BitLen % 32 != 0) {
        int bit = BitLen % 32; 
        TELEM mask = (1 << bit) - 1; 
        res.pMem[MemLen - 1] &= mask;  
    }
    
    return res;  // Возвращаем результат
}

// Возвращает длину битового поля в битах
int TBitField::GetLen() const {
    return BitLen;
}

std::ostream& operator<<(std::ostream& out, const TBitField& bf) {
    // Вывод номеров битов
    out << "Номер: ";
    for (int i = 0; i < bf.BitLen; i++) {
        out << std::setw(2) << i;
        
        if ((i + 1) % 8 == 0 && i != bf.BitLen - 1) {
            out << "  |  "; 
        } else {
            out << " ";
        }
    }
    
    // Вывод самих битов
    out << "\nБиты:  ";
    for (int i = 0; i < bf.BitLen; i++) {
        out << std::setw(2) << (bf.GetBit(i) ? '1' : '0');
        
        if ((i + 1) % 8 == 0 && i != bf.BitLen - 1) {
            out << "  |  ";
        } else if (i != bf.BitLen - 1) {
            out << " ";
        }
    }
    
    return out;
}



istream& operator>>(istream& is, TBitField& bf) {
    char ch;
    for (int i = 0; i < bf.BitLen; i++) {
        is >> ch;
        if (ch == '1') {
            bf.SetBit(i);
        } else if (ch == '0') {
            bf.ClrBit(i);
        } else {
            break;  // неверный символ — прерываем ввод
        }
    }
    return is;
}
