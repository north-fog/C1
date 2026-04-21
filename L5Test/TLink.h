#pragma once
#include "TDatValue.h"

// ”казатель на значение
typedef TDatValue* PTDatValue;

//  ласс звена списка
class TLink {
private:
    PTDatValue pValue;   // указатель на данные
    TLink* pNext;        // указатель на следующее звено

public:
    TLink(PTDatValue pVal = nullptr, TLink* pN = nullptr)
        : pValue(pVal), pNext(pN) {}
    
    ~TLink() { delete pValue; }
    
    // √еттеры и сеттеры
    PTDatValue GetValue() const { return pValue; }
    void SetValue(PTDatValue pVal) { pValue = pVal; }
    
    TLink* GetNext() const { return pNext; }
    void SetNext(TLink* pN) { pNext = pN; }
};