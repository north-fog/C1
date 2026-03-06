#pragma once
#include <iostream>
#include <sstream>  
#include <string>   
#include "TBitField.h"

class TSet
{
private:
    int MaxPower;
    TBitField BitFild;
    
public:
    TSet(int mp);
    TSet(const TSet& s);
    TSet(const TBitField& bf);
    operator TBitField();
    
    void InsLem(const int elem);
    void DelLem(const int elem);
    int isMember(const int elem) const;
    
    int operator ==(const TSet& s);
    TSet& operator =(const TSet& s);
    TSet operator+(const TSet& s);
    TSet operator*(const TSet& s);
    TSet operator~();
    
    friend std::ostream& operator<<(std::ostream& os, const TSet& s) {
        os << "{ ";
        bool flag = true;
        for (int i = 0; i < s.MaxPower; i++) {
            if (s.isMember(i)) {
                if (!flag) os << ", ";
                os << i;
                flag = false;
            }
        }
        os << " }";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, TSet& s) {
        // Очищаем множество
        for (int i = 0; i < s.MaxPower; i++) {
            s.DelLem(i);
        }
        
        // Читаем всю строку
        std::string line;
        std::getline(is, line);
        
        // Создаем поток из строки
        std::istringstream iss(line);
        int elem;
        
        // Читаем числа из строки
        while (iss >> elem) {
            if (elem >= 0 && elem < s.MaxPower) {
                s.InsLem(elem);
            }
        }
        
        return is;
    }
};