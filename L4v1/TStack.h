
#define TSTACK_H

typedef int TElem; // Тип элементов (идентификатор задания)

class TStack {
protected:
    TElem* pMem;       // Указатель на память для стека
    int MemSize;       // Размер выделенной памяти
    int DataCount;     // Количество элементов в стеке
    int Hi;            // Индекс вершины стека

public:
    TStack(int Size);           // Конструктор
    TStack(const TStack& st);   // Конструктор копирования
    virtual ~TStack();           // Виртуальный деструктор

    bool IsEmpty() const;        // Проверка на пустоту
    bool IsFull() const;         // Проверка на полноту
    virtual void Put(TElem val); // Положить элемент (виртуальный)
    virtual TElem Get();         // Взять элемент (виртуальный)

    int GetDataCount() const;    // Получить количество элементов
};
