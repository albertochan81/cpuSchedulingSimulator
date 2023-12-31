//  Alberto Chan Liu
//  SimulatedOS.cpp
//  CS340
//

#include "SimulatedOS.h"
#include "Process.h"
#include "Disks.h"
#include "RAM.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>

// Constructor
SimulatedOS:: SimulatedOS( int numberOfDisk, int amntOfRAM, int pageSiz): numberOfDisks(numberOfDisk), amountOfRAM(amntOfRAM), pageSize(pageSiz), processID(0), priority(0), processInCPU(0)
{
    // with Paramters amntOfRAM and pageSize, sets frames in RAM
    ram.SetFrames(amntOfRAM,pageSiz);
    
    //Creates disks depending on number of disks
    for( int i= 0; i <= numberOfDisk; i++)
    {
        disk.CreateVector(i+1);
        disks.push_back(disk);
    }
    
}

// Prints Process in CPU
void SimulatedOS:: PrintCPU()
{
    std::cout << "CPU: " << process.GetID(processInCPU) << std::endl;
}

// Creates New Process
void SimulatedOS:: NewProcess(int priorityNum)
{
    processID += 1;
    int page = 0;
    
    //creates a new process
    process.CreateProcess(priorityNum, processID, page);
    
    //inserts process in RAM
    ram.NewProcess(processID,page);
    
    //Check if it is the first process
    if ((readyQueue.size() == 0) && (processInCPU == 0))
    {
        processInCPU = priorityNum;
       // ram.Ram(processID);
    }
    
    //Check if readyQueue is empty and if process has more priority
    else if ((readyQueue.size() !=0) && (priorityNum > processInCPU))
    {
        readyQueue.push(processInCPU);
        processInCPU = priorityNum;
    }
    
    //Check if process has less priority and put it into readyQueue
    else if (priorityNum < processInCPU)
    {
        readyQueue.push(priorityNum);
    }
    
    // Here if readyQueu can be empty but checks if
    // process priority is bigger than the current process in CPU's
    // Put in priority queue the current rpocess and newprocess into CPU
    else if(priorityNum > processInCPU)
    {
        readyQueue.push(processInCPU);
        processInCPU = priorityNum;
    }
}

void SimulatedOS::Exit()
{
    //Deletes process data from all locations
    ram.DeleteProcessInRAM(process.GetID(processInCPU));
    process.DeleteProcess(processInCPU);
        
    //Check in readyQueue is empty
    //if not empty, set next process in readyQueue to CPU
    //if empty set CPU to process 0
    if (readyQueue.size() !=0)
    {
        processInCPU = readyQueue.top();
        ram.ProcessFromCPU(process.GetID(processInCPU), process.GetPage(process.GetID(processInCPU)));
        readyQueue.pop();
    }
    else
        processInCPU = 0;
}

// Prints Ready Queue
void SimulatedOS::PrintReadyQueue()
{
    std::cout <<"Ready-Queue: ";
    std::priority_queue<int> queue= readyQueue;
    
    while (!queue.empty())
    {
        std::cout << process.GetID(queue.top())<< " ";
        queue.pop();
    }
     std::cout << std::endl;
}

// Process reads specified file from specified disk number
void SimulatedOS::DiskReadRequested(int diskNum, std::string fileString)
{
    //Check if number of Disk is valid
    if (diskNum < numberOfDisks)
    {
        //Check if there is a process in CPU
        if(processInCPU == 0)
            {
                std::cout<< "Instruction was ignored"<<std::endl;
            }
        
        else
        {
            diskNumber = diskNum;
            fileName = fileString;
            
            //Populate selected disk with data
            disks[diskNum].PopulateDisks(diskNum, process.GetID(processInCPU) ,fileString, processInCPU);
            
            //Sets CPU to next process in readyQueu if not empty
            //Otherwise process in CPU = 0
            if (readyQueue.size() != 0)
            {
                processInCPU = readyQueue.top();
                ram.ProcessFromCPU(process.GetID(processInCPU), process.GetPage(process.GetID(processInCPU)));
                readyQueue.pop();
                ram.TimeStampIncrement(process.GetID(processInCPU));
            }
            else
            {
                processInCPU = 0;
            }
        }
    }
    
    //Error message if Disk does not exists
    else
        std::cout << "Instruction ignored: no disk with such number exists" << std::endl;
}

// Prints process and file being used in Disk
void SimulatedOS:: PrintDisk(int diskNum)
{
    // Parameter number error cheking
    if (diskNum < numberOfDisks)
    {
        //Message if Disk number has no PID
        if(disks[diskNum].GetPid(diskNum) ==-1)
        {
            std::cout <<"Disk " << diskNum <<": ";
            std::cout <<"Idle" << std::endl;
        }
        //Outputs info of disk selected
        else
        {
            std::cout <<"Disk " << diskNum <<": ";
            std::cout <<"PID "<< disks[diskNum].GetPid(diskNum)<< ", ";
            std::cout << disks[diskNum].GetFileName(diskNum)<< std::endl;
        }
    }
    
    //Error message if Disk does not exists
    else
        std::cout<< "Instruction ignored: no disk with such number exists"<<std::endl;
}

// Terminates process in Disk selected
void SimulatedOS::DiskJobCompleted(int diskNum)
{
    //Checks if Disk number is valid
    if (diskNum < numberOfDisks)
    {
        //Checks if there is a process is Disk selected
        //Then puts back running proces in readyQueue
        //Sets process in CPU and deletes process in selected disk
        if(disks[diskNum].GetPid(diskNum) !=-1)
        {
            if (processInCPU !=0)
            {
                readyQueue.push(processInCPU);
            }
            
            // Puts process in Disk  back into the CPU
            processInCPU = disks[diskNum].GetPriority(diskNum);
            
            // Sets page from process in CPU to frame if necesasary
            ram.ProcessFromCPU(process.GetID(processInCPU), process.GetPage(process.GetID(processInCPU)));
            
            // Deletes Disk data not used
            disks[diskNum].DeleteDiskData(diskNum);
            
            // Increment timestamp
            ram.TimeStampIncrement(process.GetID(processInCPU));
        }
    }
    
    //Outpuss if Disk number is not valid
    else
        std::cout<< "Instruction ignored: no disk with such number exists"<<std::endl;
}

// Outputs Disk Queue
void SimulatedOS::PrintDiskQueue(int diskNum)
{
    disks[diskNum].PrintDiskQueue(diskNum);
}

// with selected memory address function will get page and use the next frame available
void SimulatedOS::FetchFrom(unsigned int memAddress)
{
    ram.Fetch(memAddress, process.GetID(processInCPU));
    
    // Sets new page to process
    process.SetNewPage(process.GetID(processInCPU), memAddress/pageSize);

}

// Outputs RAM in a formatted way
void SimulatedOS::PrintRAM()
{
    ram.PrintRam();
}


