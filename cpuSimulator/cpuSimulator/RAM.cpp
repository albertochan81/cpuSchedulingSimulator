//  Alberto Chan Liu
//  RAM.cpp
//  CS340
//

#include "RAM.h"
#include <iomanip>

//Default values of RAM member variables
RAM::RAM(): pageSize(0), frame(0), frameLength(0), pid(-1), timeStamp(0)
{
}

//Sets the total frames
void RAM::SetFrames(int amntOfRam, int pageSiz)
{
    pageSize = pageSiz;
    frameLength = amntOfRam/pageSiz;
    
    // set default values in frames
    for( int i= 0; i < frameLength; i++) /// check -1
    {
        frameVector.push_back(i);
        framePid.insert(std::make_pair(i, -1));
        framePage.insert(std::make_pair(i,0));
    }
}


//When new process arrives sets the page table to correct process data
void RAM::NewProcess(int pID, int page)
{
    int frameNumber= 0;
    // Use to compare with other frames timeStamps
    int smallestTimeStamp = 999999;
    bool inserted = false;
    
    //When frame is set to defaults values, populate that frame
    for( int i= 0; i < frameLength; i++)
    {
        if (framePid.find(i)->second == -1)
        {
            timeStamp += 1;
            framePid.erase(i);
            framePage.erase(i);
            framePid.insert(std::make_pair(i, pID));
            framePage.insert(std::make_pair(i,0));
            frameTimeStamp.insert(std::make_pair (i,timeStamp));
            inserted=true;
        }
        
        // Checks if already populated a single frame
        if (inserted == true)
        {
            i=frameLength;
        }
    }
    if (inserted == false)
    {
        // Sets smallest timeStamp
        for( int i= 0; i < frameLength; i++)
        {
            if (smallestTimeStamp > frameTimeStamp.find(i)->second)
            {
                smallestTimeStamp = frameTimeStamp.find(i)->second;
                frameNumber = i;
            }
        }
        
        // Removes and inserts correct process data into page table
        timeStamp += 1;
        framePid.erase(frameNumber);
        framePage.erase(frameNumber);
        framePid.insert(std::make_pair(frameNumber, pID));
        framePage.insert(std::make_pair(frameNumber, page));
        frameTimeStamp.erase(frameNumber);
        frameTimeStamp.insert(std::make_pair (frameNumber,timeStamp));
        
    }
}

//Deletes process data in RAM with PID of process selected
void RAM::DeleteProcessInRAM(int pID)
{
    // Checks every frame with PID needed to delete
    // If deleted sets frame to preset default values
    for( int i= 0; i < frameLength; i++)
    {
        if (framePid.find(i)->second == pID)
        {
            framePid.erase(i);
            framePage.erase(i);
            frameTimeStamp.erase(i);
            framePid.insert(std::make_pair(i, -1));
            framePage.insert(std::make_pair(i,-1));
            frameTimeStamp.insert(std::make_pair(i,0));
        }
        
    }
}

// With parameters memAddress (Memory address) ans pID (process ID)
// Finds memory address needed to put process data on the page table
void RAM::Fetch(unsigned int memAddress, int pID)
{
    int page = memAddress/pageSize;
    int frameNumber= 0;
    
    // Use to compare with other frames timeStamps
    int smallestTimeStamp = 999999;
    bool inserted = false;
    
    for( int i= 0; i < frameLength; i++)
    {
        // Checks current frame PID and Page are already in RAM
        if ((framePid.find(i)->second == pID) && (framePage.find(i)->second == page))
        {
            inserted = true;
            timeStamp+=1;
            frameTimeStamp.erase(i);
            frameTimeStamp.insert(std::make_pair(i, timeStamp));
        }
    }
    
    // Check if frame is Empty (with default Pid) and if the process info is in RAM
    for( int i= 0; i < frameLength; i++)
    {
        // Checks if Pid is default(empty) so it can use that frame
        if ((framePid.find(i)->second == -1) && (inserted == false))
        {
            timeStamp+=1;
            framePid.erase(i);
            framePid.insert(std::make_pair(i, pID));
            framePage.erase(i);
            framePage.insert(std::make_pair(i, page));
            frameTimeStamp.erase(i);
            frameTimeStamp.insert(std::make_pair(i, timeStamp));
            i=frameLength;
            inserted = true;
        }
    }
    
   
    // If not inserted in empty frame
    // Check which frame has smaller timeStamp
    if (inserted == false)
    {
        // Sets smallest timeStamp
        for( int i= 0; i < frameLength; i++)
        {
            if (smallestTimeStamp > frameTimeStamp.find(i)->second)
            {
                smallestTimeStamp = frameTimeStamp.find(i)->second;
                frameNumber = i;
            }
        }
        // Removes and inserts correct process data into page table
        timeStamp+=1;
        framePid.erase(frameNumber);
        framePid.insert(std::make_pair(frameNumber, pID));
        framePage.erase(frameNumber);
        framePage.insert(std::make_pair(frameNumber, page));
        frameTimeStamp.erase(frameNumber);
        frameTimeStamp.insert(std::make_pair(frameNumber, timeStamp));
    }
}

//Prints RAM in a specified format
void RAM::PrintRam()
{
    std::cout <<"Frame"<< std::setw(8)<<"Page"<<std::setw(8)<< "PID" << std::endl;
    
    for( int i= 0; i < frameLength; i++)
    {
        if (framePid.find(i)->second != -1)
        {
            std::cout <<i<< std::setw(10);
            std::cout <<framePage.find(i)->second<<std::setw(10)<< framePid.find(i)->second<<std::endl;
        }
    }
}

// Increments time stamp using Pid of process
void RAM::TimeStampIncrement(int pid)
{
    for( int i= 0; i < frameLength; i++)
    {
        if (framePid.find(i)->second == pid)
        {
            timeStamp += 1;
            frameTimeStamp.erase(i);
            frameTimeStamp.insert(std::make_pair(i, timeStamp));
        }
    }
}

// Checks if process data in CPU is already in frames of RAM
void RAM::ProcessFromCPU (int pid, int page)
{
    int frameNumber= 0;
    
    // Use to compare with other frames timeStamps
    int smallestTimeStamp = 999999;
    bool inserted = false;
    
    for( int i= 0; i < frameLength; i++)
    {
        // Checks if process info (pid and page) is already in Frame
        if ((framePid.find(i)->second == pid) && (framePage.find(i)->second == page))
        {
            inserted = true;
            timeStamp+=1;
            frameTimeStamp.erase(i);
            frameTimeStamp.insert(std::make_pair(i, timeStamp));
        }
    }
    
    // If Process info is not in RAM look for smallest timestamp
    if(inserted == false)
    {
        for( int i= 0; i < frameLength; i++)
        {
            if (smallestTimeStamp > frameTimeStamp.find(i)->second)
            {
                smallestTimeStamp = frameTimeStamp.find(i)->second;
                frameNumber = i;
            }
        }
        
        // Removes and inserts correct process data into page table
        timeStamp+=1;
        framePid.erase(frameNumber);
        framePid.insert(std::make_pair(frameNumber, pid));
        framePage.erase(frameNumber);
        framePage.insert(std::make_pair(frameNumber, page));
        frameTimeStamp.erase(frameNumber);
        frameTimeStamp.insert(std::make_pair(frameNumber, timeStamp));
    }
}
