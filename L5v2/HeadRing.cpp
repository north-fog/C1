#include "HeadRing.h"

// Конструктор — создает фиктивное звено-заголовок
THeadRing::THeadRing() {
    // Создаем фиктивный заголовок (не хранит данные)
    pHead = new TDatLink(nullptr, nullptr);
    pFirst = pHead;
    pLast = pHead;
    pCurrLink = pHead;
    pPrevLink = nullptr;
    pStop = nullptr;
    CurrPos = 0;
    ListLen = 0;
}

// Деструктор — удаляет заголовок
THeadRing::~THeadRing() {
    DelList();      // удаляем все реальные звенья
    delete pHead;   // удаляем заголовок
}

// Вставка после заголовка (в начало списка)
void THeadRing::InsFirst(PTDatValue pVal) {
    // Получаем следующее звено после заголовка (приводим к PTDatLink)
      PTDatLink pNext = static_cast<PTDatLink>(pFirst->GetNextLink());
    // Создаем новое звено
    PTDatLink pNew = new TDatLink(pVal, pNext);
    
    // Устанавливаем pFirst->pNext на новое звено
    pFirst->SetNextLink(pNew);
    
    if (ListLen == 0) {
        pLast = pNew;
    }
    
    if (pCurrLink == pFirst) {
        pCurrLink = pNew;
    } else if (pCurrLink != nullptr && CurrPos > 0) {
        CurrPos++;
    }
    
    ListLen++;
}

// Удаление первого реального звена
void THeadRing::DelFirst() {
    if (ListLen == 0) return;
    
    // Получаем первое реальное звено (приводим к PTDatLink)
    PTDatLink pOld = static_cast<PTDatLink>(pFirst->GetNextLink());
    
    // Получаем следующее звено после удаляемого (приводим к PTDatLink)
    PTDatLink pNext = static_cast<PTDatLink>(pOld->GetNextLink());
    
    // Перенаправляем pFirst на следующее звено
    pFirst->SetNextLink(pNext);
    
    if (pNext == nullptr) {
        pLast = pFirst;
    }
    
    if (pOld == pCurrLink) {
        pCurrLink = pNext;
        if (pCurrLink == nullptr) {
            pCurrLink = pFirst;
        }
        if (pPrevLink == pFirst) {
            pPrevLink = nullptr;
        }
    }
    
    DelLink(pOld);
    ListLen--;
}
void THeadRing::InsLast(PTDatValue pVal) {
    PTDatLink pNew = new TDatLink(pVal, nullptr);
    
    if (ListLen == 0) {
        pHead->SetNextLink(pNew);
        pLast = pNew;
        pCurrLink = pNew;
        pPrevLink = pHead;
        CurrPos = 0;
    } else {
        pLast->SetNextLink(pNew);
        pLast = pNew;
    }
    ListLen++;
}