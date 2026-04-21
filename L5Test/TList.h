#pragma once
#include "TLink.h"

// Класс линейного списка
class TList {
private:
    TLink* pFirst;   // указатель на первое звено
    TLink* pLast;    // указатель на последнее звено
    TLink* pCurr;    // указатель на текущее звено
    int len;         // количество звеньев

public:
    // Конструктор
    TList() : pFirst(nullptr), pLast(nullptr), pCurr(nullptr), len(0) {}
    
    // Деструктор
    ~TList() { Clear(); }
    
    // Очистка списка
    void Clear() {
        while (pFirst != nullptr) {
            TLink* p = pFirst;
            pFirst = pFirst->GetNext();
            delete p;
        }
        pLast = nullptr;
        pCurr = nullptr;
        len = 0;
    }
    
    // Проверка на пустоту
    bool IsEmpty() const { return pFirst == nullptr; }
    
    // Количество звеньев
    int GetLength() const { return len; }
    
    // ========== НАВИГАЦИЯ (Итератор) ==========
    
    // Установить на начало
    void Reset() {
        pCurr = pFirst;
    }
    
    // Проверка, не конец ли списка
    bool IsEnd() const {
        return pCurr == nullptr;
    }
    
    // Перейти к следующему звену
    void GoNext() {
        if (pCurr != nullptr) {
            pCurr = pCurr->GetNext();
        }
    }
    
    // Получить текущее значение
    PTDatValue GetCurrent() const {
        return (pCurr != nullptr) ? pCurr->GetValue() : nullptr;
    }
    
    // ========== ВСТАВКА ==========
    
    // Вставка в начало
    void InsFirst(PTDatValue pVal) {
        TLink* pNew = new TLink(pVal, pFirst);
        pFirst = pNew;
        if (len == 0) {
            pLast = pNew;
        }
        len++;
    }
    
    // Вставка в конец
    void InsLast(PTDatValue pVal) {
        TLink* pNew = new TLink(pVal, nullptr);
        if (len == 0) {
            pFirst = pNew;
            pLast = pNew;
            pCurr = pNew;
        } else {
            pLast->SetNext(pNew);
            pLast = pNew;
        }
        len++;
    }
    
    // Вставка перед текущим звеном
    void InsCurrent(PTDatValue pVal) {
        if (pCurr == nullptr || len == 0) {
            InsFirst(pVal);
            return;
        }
        
        // Ищем предыдущее звено
        TLink* pPrev = nullptr;
        TLink* p = pFirst;
        while (p != nullptr && p != pCurr) {
            pPrev = p;
            p = p->GetNext();
        }
        
        TLink* pNew = new TLink(pVal, pCurr);
        if (pPrev == nullptr) {
            pFirst = pNew;
        } else {
            pPrev->SetNext(pNew);
        }
        len++;
    }
    
    // ========== УДАЛЕНИЕ ==========
    
    // Удаление первого звена
    void DelFirst() {
        if (pFirst == nullptr) return;
        
        TLink* pOld = pFirst;
        pFirst = pFirst->GetNext();
        
        if (pFirst == nullptr) {
            pLast = nullptr;
        }
        
        if (pCurr == pOld) {
            pCurr = pFirst;
        }
        
        delete pOld;
        len--;
    }
    
    // Удаление текущего звена
    void DelCurrent() {
        if (pCurr == nullptr) return;
        
        // Ищем предыдущее звено
        TLink* pPrev = nullptr;
        TLink* p = pFirst;
        while (p != nullptr && p != pCurr) {
            pPrev = p;
            p = p->GetNext();
        }
        
        if (pPrev == nullptr) {
            DelFirst();
            return;
        }
        
        pPrev->SetNext(pCurr->GetNext());
        if (pCurr == pLast) {
            pLast = pPrev;
        }
        
        TLink* pOld = pCurr;
        pCurr = pCurr->GetNext();
        delete pOld;
        len--;
    }
    
    // ========== ДОСТУП К ЗНАЧЕНИЯМ ==========
    
    // Получить значение первого звена
    PTDatValue GetFirst() const {
        return (pFirst != nullptr) ? pFirst->GetValue() : nullptr;
    }
    
    // Получить значение последнего звена
    PTDatValue GetLast() const {
        return (pLast != nullptr) ? pLast->GetValue() : nullptr;
    }
};