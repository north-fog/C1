
#define TQUEUE_H

#include "TStack.h"

class TQueue : public TStack {
protected:
    int Li; // Индекс начала очереди

    virtual int GetNextIndex(int index); // Получить следующий индекс (кольцевой буфер)

public:
    TQueue(int Size);          // Конструктор
    virtual void Put(TElem val) override; // Добавить элемент (в конец)
    virtual TElem Get() override;         // Извлечь элемент (из начала)
};