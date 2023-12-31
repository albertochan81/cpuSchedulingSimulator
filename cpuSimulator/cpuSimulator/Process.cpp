//  Alberto Chan Liu
//  Process.cpp
//  CS340
//

#include "Process.h"


//Creates new process
void Process:: CreateProcess(int priorityNum, int pID, int pag)
{
    processID = pID;
    page = pag;
    
    //Creates 3 maps to store information about Priority, PID and Page of each process
    processPage.insert(std::make_pair(processID, page));
    processMapID.insert(std::make_pair(priorityNum,processID));
    processPriority.insert(std::make_pair(processID,priorityNum));
}

//With parameter process id (pid)
//returns process id number
//if pid is invalid, returns -1
int Process:: GetID(int pid)
{
    if (processMapID.size() > 0)
        
        return processMapID.find(pid)->second;
    
    else
        return -1;
}

// Returns priority number of process using its PID
int Process::GetPriority(int pid)
{
        if (processPriority.size() > 0)
            
            return processPriority.find(pid)->second;
        
        else
            return -1;
}

// With parameter PID function returns last page used for this process
int Process::GetPage(int pid)
{
    if (processPriority.size() > 0)
        
        return processPage.find(pid)->second;
    
    else
        return 0;
}

//With parameter priority
//Deletes process and process data with that priority
void Process:: DeleteProcess (int priority)
{
    processPriority.erase(processMapID.find(priority)->second);
    processPage.erase(processMapID.find(priority)->second);
    processMapID.erase(priority);
}

// With parameters PID and Page
// Sets a new page linked to this process
void Process::SetNewPage(int pid, int page)
{
    processPage.erase(pid);
    processPage.insert(std::make_pair(pid, page));
}
