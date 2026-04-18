#include "TStack.h" 
TStack :: TStack (int Size) {// конструктор 
  DataCount = 0; 
  if (Size==0) { Size = MaxMemSize; } 
  MemSize = Size; 
  pMem = new TELEM [MemSize]; 
  Hi   = -1; } 
 
TStack :: ~TStack() {   //деструктор 
  delete []pMem; 
} 
 
int TStack :: GetNextIndex (int index) { // получить следующий индекс 
  return ++index ; 
} 
 
int TStack :: IsEmpty ( void ) const { return DataCount == 0;} 
 
int TStack :: IsFull  ( void ) const { return DataCount == MemSize;} 
 
void TStack :: Put ( const  TELEM& Val ) { // добавить значение 
    Hi++; 
    pMem[Hi] = Val; 
    DataCount++;  
} 
 
TELEM TStack :: Get ( void ) {            // извлечь значение 
  DataCount--; 
  return pMem[Hi--];  
} 
TELEM TStack::Peek(void)const{
  if (IsEmpty()) {
    return 0;  
  }
  return pMem[Hi];

}