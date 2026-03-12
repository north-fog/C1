#include "TSet.h"
#include <iostream>
using namespace std;


TSet::TSet(int mp) : MaxPower(mp), BitFild(mp) {
    // Проверка на положительную мощность
    if (mp <= 0) {
        throw "Ошибка в конструкторе TSet: мощность должна быть положительной!";
    }
}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitFild(s.BitFild) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLen()), BitFild(bf) {}



TSet::operator TBitField() {
    TBitField tmp(this->BitFild);
    return tmp;
}


void TSet::InsElem(const int elem) {
    // Проверка на отрицательный индекс
    if (elem < 0) {
        throw "Ошибка в InsElem: индекс элемента не может быть отрицательным!";
    }
    
    // Проверка на выход за границы
    if (elem >= MaxPower) {
        throw "Ошибка в InsElem: индекс элемента выходит за границы множества!";
    }
    
    // Если все проверки пройдены - устанавливаем бит
    BitFild.SetBit(elem);
}

void TSet::DelElem(const int elem) {
    // Проверка на отрицательный индекс
    if (elem < 0) {
        throw "Ошибка в DelElem: индекс элемента не может быть отрицательным!";
    }
    
    // Проверка на выход за границы
    if (elem >= MaxPower) {
        throw "Ошибка в DelElem: индекс элемента выходит за границы множества!";
    }
    
    // Если все проверки пройдены - очищаем бит
    BitFild.ClrBit(elem);
}

int TSet::isMember(const int elem) const {
    // Проверка на отрицательный индекс
    if (elem < 0) {
        throw "Ошибка в isMember: индекс элемента не может быть отрицательным!";
    }
    
    // Проверка на выход за границы
    if (elem >= MaxPower) {
        throw "Ошибка в isMember: индекс элемента выходит за границы множества!";
    }
    
    // Если все проверки пройдены - возвращаем значение бита
    return BitFild.GetBit(elem);
}



int TSet::operator==(const TSet& s) {
    return (BitFild == s.BitFild);
}

TSet& TSet::operator=(const TSet& s) {
    // Проверка на самоприсваивание
    if (this == &s) {
        cout << "Предупреждение в TSet::operator=: попытка самоприсваивания" << endl;
        return *this;
    }
    
    MaxPower = s.MaxPower;
    BitFild = s.BitFild;
    return *this;
}



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
TSet TSet::operator+ (const int elem) {
        // Проверяем границы
    if (elem < 0) {
        throw "Ошибка в operator+: индекс элемента не может быть отрицательным!";
    }
    if (elem >= MaxPower) {
        throw "Ошибка в operator+: индекс элемента выходит за границы множества!";
    }
    
    // Добавляем элемент
    BitFild.SetBit(elem);
    
    return *this;
}

TSet TSet::operator- (const int elem) {

    if (elem < 0) {
        throw "Ошибка в operator+: индекс элемента не может быть отрицательным!";
    }
    if (elem >= MaxPower) {
        throw "Ошибка в operator+: индекс элемента выходит за границы множества!";
    }
    
    // Добавляем элемент
    BitFild.ClrBit(elem);
    
    return *this;
}
