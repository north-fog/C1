#pragma once

#include "RootLink.h"

class TDatLink;
typedef TDatLink* PTDatLink;

// Звено с указателем на значение
class TDatLink : public TRootLink {
protected:
    PTDatValue pValue;  // указатель на объект значения

public:
    TDatLink(PTDatValue pVal = nullptr, PTRootLink pN = nullptr)
        : TRootLink(pN), pValue(pVal) {}
    
    void SetDatValue(PTDatValue pVal) override { pValue = pVal; }
    PTDatValue GetDatValue() const override { return pValue; }
    
    PTDatLink GetNextDatLink() const {
        return static_cast<PTDatLink>(pNext);
    }
    

    
    friend class TDatList;
};