#include "TSet.h"
#include <iostream>
using namespace std;
//расмотреть возможность переделать на  явную иницализацию

TSet::TSet(int mp):
 MaxPower(mp), 
 BitFild(mp) {}


TSet::TSet(const TSet& s): 
MaxPower(s.MaxPower), 
BitFild(s.BitFild) {}


TSet::TSet(const TBitField& bf):
MaxPower(bf.GetLen()),
BitFild(bf) {}


TSet::operator TBitField() {
    TBitField tmp(this->BitFild);  
    return tmp;                     
}


void TSet::InsElem(const int elem) {
    if (elem >= 0 && elem < MaxPower) {
        BitFild.SetBit(elem);  // Устанавливаем бит
    }
}


void TSet::DelElem(const int elem) {
    if (elem >= 0 && elem < MaxPower) {
        BitFild.ClrBit(elem);  // Очищаем соответствующий бит
    }
}

int TSet::isMember(const int elem) const {
    if (elem >= 0 && elem < MaxPower) {
        return BitFild.GetBit(elem);
    }
    return 0;
}

int TSet::operator==(const TSet& s) {
   return (BitFild == s.BitFild);
}

// Оператор присваивания
TSet& TSet::operator=(const TSet& s) {
    MaxPower = s.MaxPower;  // Копируем мощность
    BitFild = s.BitFild;    // Копируем битовое поле через оператор = класса TBitField
    return *this;           // Возвращаем ссылку на текущий объект
}

// Оператор объединения множеств (A ? B) 
TSet TSet::operator+(const TSet& s) {
    TSet res(BitFild | s.BitFild);
    return res;
}


TSet TSet::operator*(const TSet& s) {
    TSet res(BitFild & s.BitFild);
    return res;
}

TSet TSet::operator~() {
    TSet res(~BitFild);
    return res;
}
ostream& operator<<(ostream& os, const TSet& s) {
    os << "{ ";
    bool first = true;
    
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.isMember(i)) {
            if (!first) {
                os << ", ";
            }
            os << i;
            first = false;
        }
    }
    
    os << " }";
    return os;
}

istream& operator>>(istream& is, TSet& s) {
    // Очищаем множество
    for (int i = 0; i < s.MaxPower; i++) {
        s.DelElem(i);
    }
    
    int elem;
    while (is >> elem) {
        if (elem >= 0 && elem < s.MaxPower) {
            s.InsElem(elem);
        }
        if (is.peek() == '\n') {
            is.get();
            break;
        }
    }
    
    return is;
}