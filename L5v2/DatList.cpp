#include "DatList.h"

TDatList::TDatList()
    : pFirst(nullptr), pLast(nullptr), pCurrLink(nullptr),
      pPrevLink(nullptr), pStop(nullptr), CurrPos(0), ListLen(0) {}

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink) {
    return new TDatLink(pVal, pLink);
}

void TDatList::DelLink(PTDatLink pLink) {
    if (pLink != nullptr) {
        delete pLink->GetDatValue();
        delete pLink;
    }
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
    PTDatLink pLink = nullptr;
    switch (mode) {
        case FIRST_POS: pLink = pFirst; break;
        case CURRENT_POS: pLink = pCurrLink; break;
        case LAST_POS: pLink = pLast; break;
    }
    return (pLink != nullptr) ? pLink->GetDatValue() : nullptr;
}

int TDatList::SetCurrentPos(int pos) {
    if (pos < 0 || pos >= ListLen) return 0;
    Reset();
    for (int i = 0; i < pos; i++) GoNext();
    return 1;
}

int TDatList::Reset() {
    pCurrLink = pFirst;
    pPrevLink = nullptr;
    CurrPos = 0;
    return (pCurrLink != nullptr) ? 1 : 0;
}

bool TDatList::IsListEnded() const {
    return pCurrLink == nullptr;
}

int TDatList::GoNext() {
    if (pCurrLink == nullptr) return 1;
    pPrevLink = pCurrLink;
    pCurrLink = pCurrLink->GetNextDatLink();
    CurrPos++;
    return (pCurrLink == nullptr) ? 1 : 0;
}

void TDatList::InsFirst(PTDatValue pVal) {
    PTDatLink pNew = GetLink(pVal, pFirst);
    pFirst = pNew;
    if (ListLen == 0) pLast = pNew;
    if (pCurrLink != nullptr) CurrPos++;
    ListLen++;
}

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

void TDatList::DelFirst() {
    if (ListLen == 0) return;
    PTDatLink pOld = pFirst;
    pFirst = pFirst->GetNextDatLink();
    if (pFirst == nullptr) pLast = nullptr;
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

void TDatList::DelCurrent() {
    if (pCurrLink == nullptr) return;
    PTDatLink pOld = pCurrLink;
    if (pPrevLink == nullptr) {
        pFirst = pCurrLink->GetNextDatLink();
    } else {
        pPrevLink->SetNextLink(pCurrLink->GetNextDatLink());
    }
    if (pCurrLink->GetNextDatLink() == nullptr) {
        pLast = pPrevLink;
    }
    pCurrLink = pCurrLink->GetNextDatLink();
    DelLink(pOld);
    ListLen--;
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

void TDatList::DelList() {
    while (!IsEmpty()) DelFirst();
}