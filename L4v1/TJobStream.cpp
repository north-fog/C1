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
        cout <<"q1 = " << r<<" Ïîðîã = "  << JobIntåns * 100.00 <<" Çàäà÷à ïîñòóïèëà"<< endl;        
        return 1;  
    } 
    cout <<"q1 = " << r<<" Ïîðîã = "  << JobIntåns * 100.00 <<" Çàäà÷à ÍÅ ïîñòóïèëà \n"<< endl;
    return 0;  
}