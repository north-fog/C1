#pragma once



class TJobStream { 
    private: 
        double JobIntеns;    // интенсивность потока задач 
    public: 
        TJobStream (int Intеns); 
        int GetNewJob(void); // генерация нового задания 
}; 
