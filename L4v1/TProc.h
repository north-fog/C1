#pragma once

class TProc { 
    private: 
        double ProcRate;       // производительность процессора 
        int JobId;             // Id выполняемого задания 
    public: 
        TProc (int Rate); 
        int IsProcBusy(void) ; // процессор занят? 
        int RunNewJob (int JobId); // приступить к выполнению нового задания 
};
