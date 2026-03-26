#include "DatList.h"

// Конструктор
TDatList::TDatList() 
    : pFirst(nullptr), pLast(nullptr), pCurrLink(nullptr), 
      pPrevLink(nullptr), pStop(nullptr), CurrPos(0), ListLen(0) {}

// Вспомогательный метод: создание звена
PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink) {
    PTDatLink pNew = new TDatLink(pVal, pLink);
    return pNew;
}

// Вспомогательный метод: удаление звена
void TDatList::DelLink(PTDatLink pLink) {
    if (pLink != nullptr) {
        delete pLink->GetDatValue();  // удаляем значение
        delete pLink;                 // удаляем звено
    }
}

// Доступ к значению
PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
    PTDatLink pLink = nullptr;
    
    switch (mode) {
        case FIRST_POS:
            pLink = pFirst;
            break;
        case CURRENT_POS:
            pLink = pCurrLink;
            break;
        case LAST_POS:
            pLink = pLast;
            break;
    }
    
    return (pLink != nullptr) ? pLink->GetDatValue() : nullptr;
}

// Установить текущее звено по позиции
int TDatList::SetCurrentPos(int pos) {
    if (pos < 0 || pos >= ListLen) {
        return 0;  // позиция вне диапазона
    }
    
    Reset();
    for (int i = 0; i < pos; i++) {
        GoNext();
    }
    
    return 1;
}

// Установить на начало списка
int TDatList::Reset() {
    pCurrLink = pFirst;
    pPrevLink = nullptr;
    CurrPos = 0;
    return (pCurrLink != nullptr) ? 1 : 0;
}

// Проверка завершения списка
bool TDatList::IsListEnded() const {
    return pCurrLink == nullptr;
}

// Переход к следующему звену
int TDatList::GoNext() {
    if (pCurrLink == nullptr) {
        return 1;  // уже в конце
    }
    
    pPrevLink = pCurrLink;
    pCurrLink = pCurrLink->GetNextDatLink();
    CurrPos++;
    
    return (pCurrLink == nullptr) ? 1 : 0;  // 1 - конец списка, 0 - есть еще
}

// Вставка в начало
void TDatList::InsFirst(PTDatValue pVal) {
    PTDatLink pNew = GetLink(pVal, pFirst);
    pFirst = pNew;
    
    if (ListLen == 0) {
        pLast = pNew;
    }
    
    // Корректируем текущую позицию
    if (pCurrLink != nullptr) {
        CurrPos++;
    }
    
    ListLen++;
}

// Вставка в конец
void TDatList::InsLast(PTDatValue pVal) {
    PTDatLink pNew = GetLink(pVal, nullptr);
    
    if (ListLen == 0) {
        pFirst = pNew;
        pLast = pNew;
        pCurrLink = pNew;
        pPrevLink = nullptr;
        CurrPos = 0;
    } else {
        pLast->SetNextLink(pNew);
        pLast = pNew;
    }
    
    ListLen++;
}

// Вставка перед текущим звеном
void TDatList::InsCurrent(PTDatValue pVal) {
    if (pCurrLink == nullptr || ListLen == 0) {
        InsFirst(pVal);
        return;
    }
    
    PTDatLink pNew = GetLink(pVal, pCurrLink);
    
    if (pPrevLink == nullptr) {
        pFirst = pNew;
    } else {
        pPrevLink->SetNextLink(pNew);
    }
    
    pPrevLink = pNew;
    ListLen++;
    CurrPos++;
}

// Удаление первого звена
void TDatList::DelFirst() {
    if (ListLen == 0) return;
    
    PTDatLink pOld = pFirst;
    pFirst = pFirst->GetNextDatLink();
    
    if (pFirst == nullptr) {
        pLast = nullptr;
    }
    
    // Корректируем текущую позицию
    if (pOld == pCurrLink) {
        pCurrLink = pFirst;
        pPrevLink = nullptr;
        CurrPos = 0;
    } else if (pCurrLink != nullptr && CurrPos > 0) {
        CurrPos--;
    }
    
    DelLink(pOld);
    ListLen--;
}

// Удаление текущего звена
void TDatList::DelCurrent() {
    if (pCurrLink == nullptr) return;
    
    PTDatLink pOld = pCurrLink;
    
    // Корректируем указатели
    if (pPrevLink == nullptr) {
        pFirst = pCurrLink->GetNextDatLink();
    } else {
        pPrevLink->SetNextLink(pCurrLink->GetNextDatLink());
    }
    
    if (pCurrLink->GetNextDatLink() == nullptr) {
        pLast = pPrevLink;
    }
    
    // Перемещаем текущее звено
    pCurrLink = pCurrLink->GetNextDatLink();
    
    DelLink(pOld);
    ListLen--;
    
    // Если список пуст, сбрасываем позицию
    if (ListLen == 0) {
        pFirst = nullptr;
        pLast = nullptr;
        pCurrLink = nullptr;
        pPrevLink = nullptr;
        CurrPos = 0;
    } else if (pCurrLink == nullptr) {
        CurrPos = ListLen;
    }
}

// Удаление всего списка
void TDatList::DelList() {
    while (!IsEmpty()) {
        DelFirst();
    }
}
