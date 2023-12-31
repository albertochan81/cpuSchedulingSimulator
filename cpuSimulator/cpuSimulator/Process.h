//  Alberto Chan Liu
//  Process.hpp
//  CS340
//

#ifndef Process_h
#define Process_h
#include "Disks.h"
#include <map>
#include <queue>

class Process{
    
public:
    
    void CreateProcess(int pid, int priority, int counter);
    
    //Getters to get process information
    int GetID(int priority);
    int GetPriority(int pid);
    int GetPage( int pid);
    
    //Functions to delete and set a different page to a process
    void DeleteProcess (int priority);
    void SetNewPage(int pid, int page);
    
    
private:
    int priority;
    int pid;
    int page;
    int processID;
    std::map <int, int> processMapID;    
    std::map <int, int> processPriority;
    std::map <int,int> processPage;
};


#endif
