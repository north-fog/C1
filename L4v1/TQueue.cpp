#include "TQueue.h"
#include <iostream>
using namespace std;

TQueue::TQueue(int Size) : TStack(Size) {
    Li = 0; // Начало очереди
    Hi = -1;
    DataCount = 0;
}

int TQueue::GetNextIndex(int index) {
    return  ++ index % MemSize ;
}

void TQueue::Put(TElem val) {
    if (IsFull()) {
        cerr << "Очередь переполнена!" << endl;
        exit(1);
    }
    Hi = GetNextIndex(Hi);
    pMem[Hi] = val;
    DataCount++;
}

TElem TQueue::Get() {
    if (IsEmpty()) {
        cerr << "Очередь пуста!" << endl;
        exit(1);
    }
    TElem tmp = pMem[Li];
    Li = GetNextIndex(Li);
    DataCount--;
    return tmp;
}