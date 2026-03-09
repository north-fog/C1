#pragma once  // Защита от повторного включения

#include <iostream>   
#include "TBitField.h"  // Подключаем класс битового поля

// Класс TSet - реализация множества на основе битового поля
// Хранит множество целых чисел от 0 до MaxPower-1
class TSet
{
private:
    int MaxPower;      // Максимальная мощность множества (размер универсума)
    TBitField BitFild; // Битовое поле для хранения характеристического вектора
    // Если бит i = 1, то число i принадлежит множеству
    
public:
    // Конструкторы
    
    // Создает пустое множество заданной мощности
    // Например: TSet(100) создает множество для чисел 0..99
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
    
    // Объединение множеств (A ? B)
    TSet operator+(const TSet& s);
    
    // Пересечение множеств (A ? B)
    TSet operator*(const TSet& s);
    
    // Дополнение множества (¬A) - все элементы, кроме тех, что в A
    TSet operator~();
    
    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const TSet& s);
    friend std::istream& operator>>(std::istream& is, TSet& s);    

    
};