//  Alberto Chan Liu
//  SimulatedOS.hpp
//  CS340
//


#ifndef SimulatedOS_h
#define SimulatedOS_h
#include "Process.h"
#include "Disks.h"
#include "RAM.h"
#include <string>
#include <queue>
#include <map>

class SimulatedOS
{
    
public:
    
    //SimulatedOS{};
    
    SimulatedOS(int numberOfDisks, int amountOfRAM, int pageSize); //
    void NewProcess(int priority); //
    void Exit(); //
    void DiskReadRequested(int diskNumber, std::string fileName); //
    void FetchFrom ( unsigned int memoryAddress);
    void DiskJobCompleted (int diskNumber); //
    void PrintCPU(); //
    void PrintReadyQueue(); //
    void PrintRAM();
    void PrintDisk( int diskNumber); //
    void PrintDiskQueue(int diskNumber);
    
        void PrintCPU2();
    void Print();
    
private:
    int numberOfDisks;
    int amountOfRAM;
    int pageSize;
    int priority;
    int diskNumber;
    int processID;
    int processInCPU;
    unsigned int memoryAddress;
    std::string fileName;
    std::vector<Disks> disks;
    std::priority_queue<int> readyQueue;
    Process process;
    Disks disk;
    RAM ram;
};

#endif /* SimulatedOS_hpp */
