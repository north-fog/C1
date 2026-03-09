#pragma once  

#include <iostream>  // Для ввода/вывода

typedef unsigned int TELEM;

class TBitField
{
private:
    // Приватные поля класса (доступны только внутри класса)
    int BitLen;      
    TELEM *pMem;    
    int MemLen;     

    int GetMemIndex(const int n) const;
    TELEM GetMemMask(const int n) const;

public:
    // Конструкторы и деструктор
    
    TBitField(const int len); 

    TBitField(const TBitField& bf);
    
    ~TBitField();
    
    
    // Возвращает длину битового поля в битах
    int GetLen() const;
    
    // Операции с отдельными битами
    
    // Устанавливает n-й бит в 1 (включает)
    void SetBit(const int n);
    
    // Устанавливает n-й бит в 0 (выключает, очищает)
    void ClrBit(const int n);
    
    // Возвращает значение n-го бита (1 или 0)
    int GetBit(const int n) const;
    
    // Перегруженные операторы
    
    // Оператор присваивания: копирует содержимое bf в текущий объект
    TBitField& operator=(const TBitField& bf);
    
    // Оператор сравнения: проверяет, равны ли два битовых поля
    int operator==(const TBitField& bf);
    
    // Оператор И (побитовое И) для двух битовых полей
    // Используется для пересечения множеств
    TBitField operator&(const TBitField &bf);
    
    // Оператор ИЛИ (побитовое ИЛИ) для двух битовых полей
    // Используется для объединения множеств
    TBitField operator|(const TBitField &bf);
    
    // Оператор НЕ (побитовое отрицание) для битового поля
    // Используется для дополнения множества
    TBitField operator~();
    
    // Оператор вывода: 
    friend std::ostream& operator<<(std::ostream& out, const TBitField& bf);
    friend std::istream& operator>>(std::istream& is, TBitField& bf);

};
