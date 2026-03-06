#pragma once
class Smart_array
{
    public:
    Smart_array();
    Array_max();
    Array_min();
    Array_search();
    Array_index();

    ~Smart_array();

    private:
        T* _array;
        size_t _size;
        size_t _count;
};