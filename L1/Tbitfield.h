#pragma once
#include <iostream>

// Определение типа для хранения битов - беззнаковое целое (обычно 4 байта = 32 бита)
typedef unsigned int TELEM;

class TBitField {
    int BitLen;      // Количество битов в поле
    TELEM* pMem;     // Указатель на массив, хранящий биты
    int MemLen;      // Длина массива pMem (в элементах TELEM)

    // Вспомогательные методы (приватные):
    int GetMemIndex(const int n) const;      // Получить индекс элемента в pMem для бита n
    TELEM GetMemMask(const int n) const;     // Получить маску для доступа к биту n внутри элемента

public:
    // Основные операции с битами:
    void SetBit(int n);          // Установить бит n в 1
    void ClearBit(int n);        // Установить бит n в 0
    bool GetBit(int n) const;    // Получить значение бита n

    // Перегруженные операторы:
    TBitField& operator=(const TBitField& bf);    // Оператор присваивания
    int operator==(const TBitField& bf);          // Сравнение на равенство (возвращает int, а не bool - устаревший стиль)
    TBitField operator&(const TBitField& bf);     // Побитовое И (пересечение множеств)
    TBitField operator|(const TBitField& bf);     // Побитовое ИЛИ (объединение множеств)
    
    // Дружественные функции для ввода/вывода:
    friend std::ostream& operator<<(std::ostream& out, const TBitField& bf);
    friend std::istream& operator>>(std::istream& is, TBitField& bf);

    // Конструкторы и деструктор:
    TBitField();                            // Конструктор по умолчанию
    TBitField(int len);                     // Конструктор с заданным размером
    TBitField(const TBitField& bf);         // Конструктор копирования
    ~TBitField();                           // Деструктор

    // Метод доступа:
    int getlen() const;                     // Получить BitLen (количество битов)
};