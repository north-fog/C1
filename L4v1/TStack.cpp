#include "TStack.h"
#include <cstdlib>
#include <iostream>
using namespace std;

TStack::TStack(int Size) {
    MemSize = Size;
    pMem = new TElem[MemSize];
    DataCount = 0;
    Hi = -1;
}

TStack::TStack(const TStack& st) {
    MemSize = st.MemSize;
    DataCount = st.DataCount;
    Hi = st.Hi;
    pMem = new TElem[MemSize];
    for (int i = 0; i < MemSize; i++)
        pMem[i] = st.pMem[i];
}

TStack::~TStack() {
    delete[] pMem;
}

bool TStack::IsEmpty() const {
    return DataCount == 0;
}

bool TStack::IsFull() const {
    return DataCount == MemSize;
}

void TStack::Put(TElem val) {
    if (IsFull()) {
        cerr << "Стек переполнен!" << endl;
        exit(1);
    }
    pMem[++Hi] = val;
    DataCount++;
}

TElem TStack::Get() {
    if (IsEmpty()) {
        cerr << "Стек пуст!" << endl;
        exit(1);
    }
    DataCount--;
    return pMem[Hi--];
}

int TStack::GetDataCount() const {
    return DataCount;
}