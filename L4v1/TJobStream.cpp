#include "TJobStream.h"
#include <cstdlib>
#include <iostream>
using namespace std;


TJobStream::TJobStream(int Intens) {
    JobIntåns = Intens / 100.0;  
}

int TJobStream::GetNewJob() {

    int r = rand() % 100;
    
    if (r < JobIntåns * 100.00) {
        cout <<"q = " << r<< " ïîñòóïèëà \n"<< endl;
        cout <<"Ïîðîã = " << JobIntåns * 100.00 << " \n"<< endl;
        

        return 1;  
    } 
    cout <<"q = " << r<< " ÍÅ ïîñòóïèëà \n"<< endl;
    cout <<"Ïîðîã = " << JobIntåns * 100.00 << " \n"<< endl;
    return 0;  
}