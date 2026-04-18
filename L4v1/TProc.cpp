#include "TProc.h"

TProc::TProc(int Rate) {
    ProcRate = Rate / 100.0; 
    JobId = -1;  
}

int TProc::IsProcBusy() {
    return (JobId != -1);  
}

int TProc::RunNewJob(int NewJobId) {
    if (IsProcBusy()) {
        return 0;  
    }
    JobId = NewJobId;
    return 1;  
}