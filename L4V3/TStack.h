const int MaxMemSize = 25; // максимальный размер памяти для стека 
typedef int TELEM;        
// тип элемента СД 
typedef TELEM *PTElem;  
// тип указателя на СД 
class TStack { 
protected:  // поля 
    PTElem pMem;   // указатель на массив элементов  
    int MemSize;    
    // размер памяти для СД 
    int DataCount;  // количество элементов в СД 
    int Hi;         
    // индекс вершины стека 
    virtual int GetNextIndex (int index); // получить следующий индекс 
    public: 
    TStack (int Size = MaxMemSize);//конструктор 
    ~TStack();                     
    //деструктор 
    int IsEmpty ( void ) const ;   
    // контроль пустоты 
    int IsFull  ( void ) const ;   
    // контроль переполнения 
    void  Put ( const TELEM &Val );// добавить значение 
    virtual TELEM Get ( void ) ;
    TELEM Peek(void) const;   
    // извлечь значение 
}; 