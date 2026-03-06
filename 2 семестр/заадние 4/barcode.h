using namespace std;

#pragma once

class Barcode{
public:

    Barcode();
    ~Barcode();
    void Barcode_init();



private:

    char barcode;
    char name;
    int price_unit;
    
    int price_general;

};