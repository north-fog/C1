#pragma once

#include "DatLink.h"

// Тип позиции для доступа к звеньям
enum TLinkPos { FIRST_POS, CURRENT_POS, LAST_POS };

// Класс линейных списков
class TDatList {
protected:
    PTDatLink pFirst;     // первое звено
    PTDatLink pLast;      // последнее звено
    PTDatLink pCurrLink;  // текущее звено
    PTDatLink pPrevLink;  // звено перед текущим
    PTDatLink pStop;      // значение указателя, означающего конец списка
    int CurrPos;          // номер текущего звена (нумерация от 0)
    int ListLen;          // количество звеньев в списке

protected:
    // Вспомогательные методы
    PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
    void DelLink(PTDatLink pLink);  // удаление звена

public:
    TDatList();
    virtual ~TDatList() { DelList(); }
    
    // Доступ
    PTDatValue GetDatValue(TLinkPos mode = CURRENT_POS) const;  // значение
    virtual bool IsEmpty() const { return pFirst == pStop; }    // список пуст?
    int GetListLength() const { return ListLen; }                // количество звеньев
    
    // Навигация
    int SetCurrentPos(int pos);          // установить текущее звено
    int GetCurrentPos() const { return CurrPos; }  // получить номер текущего звена
    virtual int Reset();                 // установить на начало списка
    virtual bool IsListEnded() const;    // список завершен?
    int GoNext();                        // сдвиг вправо текущего звена
    
    // Вставка звеньев
    virtual void InsFirst(PTDatValue pVal = nullptr);   // перед первым
    virtual void InsLast(PTDatValue pVal = nullptr);    // вставить последним
    virtual void InsCurrent(PTDatValue pVal = nullptr); // перед текущим
    
    // Удаление звеньев
    virtual void DelFirst();      // удалить первое звено
    virtual void DelCurrent();    // удалить текущее звено
    virtual void DelList();       // удалить весь список
};