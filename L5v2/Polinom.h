#pragma once

#include "HeadRing.h"
#include "Monom.h"

typedef TMonom* PTMonom;

// Класс полинома (список мономов)
class TPolinom : public THeadRing {
public:
    // Конструктор из массива «коэффициент-индекс»
    TPolinom(int monoms[][2] = nullptr, int km = 0);
    
    // Конструктор копирования
    TPolinom(const TPolinom& q);
    
    // Получить текущий моном
    PTMonom GetMonom() { return static_cast<PTMonom>(GetDatValue()); }
    
    // Операторы
    TPolinom& operator+(const TPolinom& q);   // сложение полиномов
    TPolinom& operator=(const TPolinom& q);   // присваивание
};