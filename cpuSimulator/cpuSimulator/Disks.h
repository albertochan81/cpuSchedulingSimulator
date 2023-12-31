//  Alberto Chan Liu
//  Disks.hpp
//  CS340
//

#ifndef Disks_hpp
#define Disks_hpp
#include "Process.h"
#include <string>
#include <iostream>
#include <map>
#include <queue>

class Disks
{
public:
    Disks();
    
    // Creates disknumber vectors depending on how many disks there are
    void CreateVector(int diskNumber);
    void PopulateDisks(int diskNumber, int pid, std::string file, int priority);
    
    // Getter function for Disk
    int GetPid(int diskNumber);
    std::string GetFileName (int diskNumber);
    void GetDiskInfo(int diskNumber);
    int GetPriority(int diskNum);
    
    // Delete and print functions
    void DeleteDiskData(int diskNumber);
    void PrintDiskQueue(int diskNumber);
    
private:
    int diskNumber;
    int pid;
    int priority;
    std::string file;
    std::priority_queue <int> diskQueue;
    std::map<int, std::string> diskFile;
    std::map <int, int> diskPid;
    std::map <int, int> diskProcessPriority;
};

#endif 
