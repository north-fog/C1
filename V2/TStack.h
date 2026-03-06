// #pragma once
// #include <iostream>
// #include <stdexcept>

// class TStack
// {
//     int top;
//     size_t memSize;
//     int* pMem;  // Используем int вместо шаблонного типа T

// public:
//     TStack(size_t _memSize = 25);
//     ~TStack();
//     TStack(const TStack& other);
//     TStack& operator=(const TStack& other);
    
//     size_t size() const;
//     bool IsEmpty() const;
//     bool IsFull() const;
//     int Pop();                   // Возвращает int
//     void Push(const int& val);   // Принимает int
//     int Peek() const;            // Возвращает int
// };
#include <iostream>

template<typename T>
class TStack
{
    int top;                                                                                    // Индекс верхнего элемента стека
    size_t memSize;                                                                             // Текущая вместимость стека
    T* pMem;                                                                                    // Указатель
     // метод для увеличения размера стека при переполнении
    void resize() {                                                                             
        size_t newSize = memSize * 2;                                                           
        T* newMem = new T[newSize];
        for (int i = 0; i <= top; i++) {
            newMem[i] = pMem[i];
        }
        delete[] pMem;
        pMem = newMem;
        memSize = newSize;                                                                     // Обновляем размер
    }

public:
    TStack(size_t _memSize = 10) : top(-1), memSize(_memSize), pMem(new T[memSize]) {}               // Конструктор с параметром по умолчанию
    ~TStack() {delete[] pMem;}                                                                       // Деструктор
    TStack(const TStack& other) : top(other.top), memSize(other.memSize), pMem(new T[memSize]) {     // Конструктор копирования
        for (int i = 0; i <= top; i++) {
            pMem[i] = other.pMem[i];
        }
    }
    
// Оператор присваивания    
   TStack& operator=(const TStack& other) {
        if (this != &other) {
            delete[] pMem;
            top = other.top;
            memSize = other.memSize;
            pMem = new T[memSize];
            for (int i = 0; i <= top; i++) {
                pMem[i] = other.pMem[i];
            }
        }
        return *this;
    }

    size_t size() const {return top + 1;}                                                       // Возвращает количество элементов в стеке
    bool IsEmpty() const {return top == -1;}                                                    // Проверяка пуст ли стек
    bool IsFull() const {return top == static_cast<int>(memSize) - 1;}                          // Проверка заполнен ли стек
// Возвращает значение верхнего элемента
    T Pop() {return pMem[top--];}
    void Push(const T& val) {                                                                   // Добавление элемент в стек
        if (IsFull()) {
            resize();
        }
        pMem[++top] = val;
    }
    T Peek() const {return pMem[top];}                                                          // Просмотр верхнего элемента без его извлечения
};