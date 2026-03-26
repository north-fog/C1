#pragma once

#include "DatValue.h"

class TRootLink;
typedef TRootLink* PTRootLink;

// Указатель на значение (нужно для методов SetDatValue/GetDatValue)
typedef TDatValue* PTDatValue;

// Базовый класс для звеньев списка
class TRootLink {
protected:
    PTRootLink pNext;  // указатель на следующее звено

public:
    TRootLink(PTRootLink pN = nullptr) : pNext(pN) {}
    
    // Доступ к следующему звену
    PTRootLink GetNextLink() const { return pNext; }
    void SetNextLink(PTRootLink pLink) { pNext = pLink; }
    
    // Вставка звена после текущего
    void InsNextLink(PTRootLink pLink) {
        PTRootLink p = pNext;
        pNext = pLink;
        if (pLink != nullptr) {
            pLink->pNext = p;
        }
    }
    
    // Чисто виртуальные методы для работы со значением
    virtual void SetDatValue(PTDatValue pVal) = 0;
    virtual PTDatValue GetDatValue() const = 0;
    
    friend class TDatList;
};