#include "TJobStream.h"
#include <cstdlib>

TJobStream::TJobStream(int Intens) {
    JobIntåns = Intens / 100.0;  
}

int TJobStream::GetNewJob() {

    int r = rand() % 100;

    if (r < JobIntåns * 100) {
        return 1;  
    } 
    return 0;  
}