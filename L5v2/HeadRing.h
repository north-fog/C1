#pragma once

#include "DatList.h"

// ÷иклический список с заголовком
class THeadRing : public TDatList {
protected:
    PTDatLink pHead;     // заголовок (фиктивное звено), pFirst Ч звено за pHead

public:
    THeadRing();
    ~THeadRing();
    
    // ¬ставка звеньев (после заголовка)
    virtual void InsFirst(PTDatValue pVal = nullptr);
    
    // ”даление звеньев (удалить первое звено)
    virtual void DelFirst();
};