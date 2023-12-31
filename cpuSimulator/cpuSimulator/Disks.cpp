// Alberto Chan Liu
//  Disks.cpp
//  CS340
//

#include "Disks.h"

//Disks Constructor
Disks::Disks()
{
    priority = 0;
    diskNumber = 0;
    pid = 0;
    file= "";
}

//Creates new Disk
void Disks::CreateVector(int diskNum)
{
    diskNumber = diskNum;
}

//Populates a selected disk with process data in parameters
void Disks::PopulateDisks(int diskNum, int pID, std::string fileN, int priority)
{
    //Checks if is the first process in que I/O queue
    if ((diskQueue.size() ==0) && (pid > 0))
    {
        diskQueue.push(pID);
    }
    //Checks if is the second process in que I/O queue
    else if (diskQueue.size() >0)
    {
        diskQueue.push(pID);
    }
    
    // Populating all data in Disk
    diskNumber = diskNum;
    pid = pID;
    file = fileN;
    diskFile.insert(std::make_pair(diskNum,file));
    diskPid.insert(std::make_pair(diskNum, pid));
    diskProcessPriority.insert(std::make_pair(diskNum, priority));
    
}

// With parameter disk number
// Returns the process pid using disk
int Disks::GetPid(int diskNum)
{
    std::map<int,int>::iterator it;
    it =diskPid.find(diskNum);
    
    // Checks if there is a process is Disk selected
    // else return -1
    if (it != diskPid.end())
    {
        return diskPid.find(diskNum)->second;
    }
   
    return -1;
}

// With parameter disk number, gets the filename
std::string Disks::GetFileName (int diskNum)
{
    return diskFile.find(diskNum)->second;;
}

//Deletes data of selected disk
void Disks::DeleteDiskData(int diskNum)
{
    diskFile.erase(diskNum);
    diskPid.erase(diskNum);
    diskProcessPriority.erase(diskNum);
    
    if (diskQueue.size()>0)
    {
        diskQueue.pop();
    }
}

// With parameter disk number, gets the priority of process
int Disks::GetPriority(int diskNum)
{
    return diskProcessPriority.find(diskNum)->second;;
}

// With parameter disk number, outputs I/O queue
void Disks::PrintDiskQueue(int diskNum)
{
    // Checks if disk number exists
    if (diskNum > diskNumber)
        std::cout<< "Instruction ignored: no disk with such number exists" << std::endl;
    
    // Checks if there is a process in Disk Queue
    else if (diskQueue.size() > 0)
    {
        std::priority_queue<int> queue= diskQueue;//
        std::cout<< "Disk "<< diskNum << " "<< "I/O-queue: ";
       
        // Outputs queue one by one
        while (!queue.empty())
        {
            std::cout << queue.top()<< " ";
            queue.pop();
        }
        std::cout<< std::endl;
    }
    
    //Output message if disk number does not exists
    else
        std::cout<<"Disk "<< diskNum << " I/O-queue: Empty" <<std::endl;
    
}
