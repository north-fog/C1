#pragma once
#include <iostream>

template<typename T>
class smart_array
{
private:
    T* _array;
    size_t _size;
    size_t _count;
public:
    smart_array(){
        _size = 5;
        _count = 0;
        _array = new T[_size];
    };
    smart_array(size_t size){
        _size = size;
        _count = 0;
        _array = new T[_size];
    };
    void Append(T elem){
        if (_count == _size){
            int* array = new int[_size];
            for(int i = 0; i < _size; i++)
            array[i] = _array[i];
            delete [] _array;
            _size++;
            _array = array;
        }
        _array[_count++] = elem;
    };
    bool FindElem(T elem){
        for(int i = 0; i < _count; i++){
            if(elem == _array[i]) return true;
        }
        return false;
    };
    T GetMax(){
        T x = _array[0];
        for(int i = 1; i < _count; i++){
            if(x < _array[i]) x = _array[i];
        }
        return x;
    };
    T GetMin(){
        T x = _array[0];
        for(int i = 1; i < _count; i++){
            if(x > _array[i]) x = _array[i];
        }
        return x;
    };
    ~smart_array(){
        delete [] _array;
    };
};
