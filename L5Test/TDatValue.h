#pragma once
class TDatValue {
public:
    virtual TDatValue* GetCopy() = 0;  // создать копию
    virtual ~TDatValue() {}
};