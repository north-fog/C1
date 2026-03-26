#pragma once

#include "RootLink.h"

class TDatLink;
typedef TDatLink* PTDatLink;

// Класс для звеньев списка с указателем на объект-значение
class TDatLink : public TRootLink {
protected:
    PTDatValue pValue;  // указатель на объект значения

public:
    TDatLink(PTDatValue pVal = nullptr, PTRootLink pN = nullptr)
        : TRootLink(pN), pValue(pVal) {}
    
    // Доступ к значению
    void SetDatValue(PTDatValue pVal) override { pValue = pVal; }
    PTDatValue GetDatValue() const override { return pValue; }
    
    // Получение следующего звена как TDatLink
    PTDatLink GetNextDatLink() const { return static_cast<PTDatLink>(pNext); }
    
    friend class TDatList;
};