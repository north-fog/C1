#include "Polinom.h"
#include <iostream>
using namespace std;

// Вспомогательная функция для декодирования индекса в степени
void DecodeIndex(int index, int& a, int& b, int& c) {
    a = index / 100;
    b = (index % 100) / 10;
    c = index % 10;
}

// Конструктор из массива {коэффициент, индекс}
TPolinom::TPolinom(int monoms[][2], int km) {
    // Инициализация (создание заголовка)
    pHead = new TDatLink(nullptr, nullptr);
    pFirst = pHead;
    pLast = pHead;
    pCurrLink = pHead;
    pPrevLink = nullptr;
    pStop = nullptr;
    CurrPos = 0;
    ListLen = 0;
    
    // Добавляем мономы
    for (int i = 0; i < km; i++) {
        if (monoms[i][0] != 0) {
            TMonom* pM = new TMonom(monoms[i][0], monoms[i][1]);
            InsLast(pM);
        }
    }
}

// Конструктор копирования
TPolinom::TPolinom(const TPolinom& q) : THeadRing() {
    PTDatLink p = static_cast<PTDatLink>(q.pFirst->GetNextLink());
    while (p != nullptr) {
        TMonom* pM = static_cast<TMonom*>(p->GetDatValue()->GetCopy());
        InsLast(pM);
        p = static_cast<PTDatLink>(p->GetNextLink());
    }
}

// Оператор присваивания
TPolinom& TPolinom::operator=(const TPolinom& q) {
    if (this == &q) return *this;
    
    DelList();
    
    PTDatLink p = static_cast<PTDatLink>(q.pFirst->GetNextLink());
    while (p != nullptr) {
        TMonom* pM = static_cast<TMonom*>(p->GetDatValue()->GetCopy());
        InsLast(pM);
        p = static_cast<PTDatLink>(p->GetNextLink());
    }
    
    return *this;
}

// Оператор сложения полиномов
TPolinom& TPolinom::operator+(const TPolinom& q) {
    TPolinom* result = new TPolinom();
    
    // Копируем все мономы из первого полинома
    PTDatLink p1 = static_cast<PTDatLink>(this->pFirst->GetNextLink());
    while (p1 != nullptr) {
        TMonom* pM = static_cast<TMonom*>(p1->GetDatValue()->GetCopy());
        result->InsLast(pM);
        p1 = static_cast<PTDatLink>(p1->GetNextLink());
    }
    
    // Добавляем мономы из второго полинома с приведением подобных
    PTDatLink p2 = static_cast<PTDatLink>(q.pFirst->GetNextLink());
    while (p2 != nullptr) {
        TMonom* pM2 = static_cast<TMonom*>(p2->GetDatValue());
        int index = pM2->GetIndex();
        int coeff = pM2->GetCoeff();
        
        // Ищем моном с таким же индексом в результате
        bool found = false;
        PTDatLink pRes = static_cast<PTDatLink>(result->pFirst->GetNextLink());
        while (pRes != nullptr) {
            TMonom* pMRes = static_cast<TMonom*>(pRes->GetDatValue());
            if (pMRes->GetIndex() == index) {
                int newCoeff = pMRes->GetCoeff() + coeff;
                if (newCoeff == 0) {
                    // Удаляем моном — используем SetCurrentPos из списка
                    int pos = result->GetCurrentPos();
                    result->SetCurrentPos(pos);
                    result->DelCurrent();
                } else {
                    pMRes->SetCoeff(newCoeff);
                }
                found = true;
                break;
            }
            pRes = static_cast<PTDatLink>(pRes->GetNextLink());
        }
        
        if (!found && coeff != 0) {
            TMonom* pNew = new TMonom(coeff, index);
            result->InsLast(pNew);
        }
        
        p2 = static_cast<PTDatLink>(p2->GetNextLink());
    }
    
    return *result;
}
