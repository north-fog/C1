#pragma once  // Защита от повторного включения

#include <iostream>   
#include "TBitField.h"  // Подключаем класс битового поля


class TSet
{
private:
    int MaxPower;      
    TBitField BitFild; 
    
public:
    // Конструкторы
    
    TSet(int mp);
    
    // Конструктор копирования
    TSet(const TSet& s);
    TSet(const TBitField& bf);
    operator TBitField();
    
    // Методы для работы с элементами множества
    
    // Добавляет элемент в множество (устанавливает соответствующий бит)
    void InsElem(const int elem);
    
    // Удаляет элемент из множества (очищает соответствующий бит)
    void DelElem(const int elem);
    
    // Проверяет, принадлежит ли элемент множеству
    // Возвращает 1 - да, 0 - нет
    int isMember(const int elem) const;
    
    // Перегруженные операторы
    
    // Сравнение множеств на равенство
    int operator ==(const TSet& s);
    
    // Присваивание множеств
    TSet& operator =(const TSet& s);
    
    // Объединение множеств (A И B)
    TSet operator+(const TSet& s);
    
    // Пересечение множеств (A Или B)
    TSet operator*(const TSet& s);
    
    // Дополнение множества (¬A) - все элементы, кроме тех, что в A
    TSet operator~();
    
    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const TSet& s);
    friend std::istream& operator>>(std::istream& is, TSet& s);    

    
};