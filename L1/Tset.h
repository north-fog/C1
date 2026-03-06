#pragma once
#include "Tbitfield.h"  

class TSet {
    int maxpower;        // Максимальная мощность множества (размер универсума)
    TBitField bitfield;  // Битовое поле для хранения элементов множества
    
public:
    // Конструкторы:
    TSet(int mp);                       // Создать пустое множество с заданным размером универсума
    TSet(const TSet& s);                // Конструктор копирования
    TSet(const TBitField& bf);          // Создать множество из битового поля
    
    // Оператор преобразования:
    operator TBitField();               // Преобразование TSet в TBitField
    
    // Основные операции с элементами:
    void inslen(int n);                 // Добавить элемент n в множество (insert element)
    void dellen(const int n);           // Удалить элемент n из множества (delete element)
    bool isMember(int n) const;         // Проверить, принадлежит ли элемент n множеству
    
    // Операторы:
    int operator==(const TSet& s);      // Проверка на равенство множеств
    TSet& operator=(const TSet& s);     // Присваивание множеств
    TSet operator+(const TSet& s);      // Объединение множеств
    TSet operator*(const TSet& s);      // Пересечение множеств
    
    // Дружественные функции для ввода/вывода:
    friend std::ostream& operator<<(std::ostream& out, const TSet& s);
    friend std::istream& operator>>(std::istream& is, TSet& s);
};