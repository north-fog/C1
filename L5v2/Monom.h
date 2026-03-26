#pragma once

#include "DatValue.h"

// Класс монома (коэффициент + индекс)
class TMonom : public TDatValue {
protected:
    int Coeff;   // коэффициент монома
    int Index;   // индекс (свертка степеней: A*100 + B*10 + C)

public:
    TMonom(int cval = 1, int ival = 0) : Coeff(cval), Index(ival) {}
    
    virtual TDatValue* GetCopy() override;  // создание копии
    
    void SetCoeff(int cval) { Coeff = cval; }
    int GetCoeff() const { return Coeff; }
    
    void SetIndex(int ival) { Index = ival; }
    int GetIndex() const { return Index; }
    
    TMonom& operator=(const TMonom& tm) {
        Coeff = tm.Coeff;
        Index = tm.Index;
        return *this;
    }
    
    int operator==(const TMonom& tm) const {
        return (Coeff == tm.Coeff) && (Index == tm.Index);
    }
    
    int operator<(const TMonom& tm) const {
        return Index < tm.Index;
    }
    
    friend class TPolinom;
};