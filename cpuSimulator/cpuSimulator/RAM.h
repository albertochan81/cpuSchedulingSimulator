//  Alberto Chan Liu
//  RAM.hpp
//  CS340
//

#ifndef RAM_h
#define RAM_h
#include <iostream>
#include <vector>
#include <map>

class RAM
{
public:
    RAM(); // constructor to set variables to default
    void NewProcess(int pid, int page); // Creates
    void SetFrames(int amntOfRam, int pageSiz); // Sets frames default values
    void DeleteProcessInRAM( int pid); // Deletes selected process data in RAM
    void Fetch(unsigned int memAddress, int processInCPU); // Fetches instruction from RAM at specific location
    void TimeStampIncrement(int pid); // Time stamp for in RAM
    void ProcessFromCPU (int pid, int page); // Updates Frame data is process in CPU is changed and
    void PrintRam(); // Prints RAM in a formatted mode
    
private:
    std::vector<int> frameVector;
    std::map<int,int> framePage;
    std::map<int,int> framePid;
    std::map<int,int> frameTimeStamp;
    int frameLength;
    int frame;
    int pageSize;
    int pid;
    int timeStamp;
    
    
};

#endif 
