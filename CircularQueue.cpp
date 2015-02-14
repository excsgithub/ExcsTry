// CircularQueue.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <windows.h> 

#include "stdafx.h"
#include "string"
#include <stdexcept>

typedef int DATA; 


//class Excpetion
//{
//public:
//    
//    Excpetion(std::string s):message(s)
//    {}
//protected:
//    std::string message;
//};

class CircularQueue
{

    

public:
    size_t arrSize;

protected:
    size_t writeInd;
    size_t readInd;
    bool lastActionIsWrite;
    //bool wasLastWrite;

    DATA * dataArr;
public: //  CTOR DTOR functions
    CircularQueue(size_t size):arrSize(size),writeInd(0),readInd(0),lastActionIsWrite(false)
    {
        dataArr = new DATA[arrSize];
        std::cout << "ctor done" << std::endl;
    }

    CircularQueue(CircularQueue & other):arrSize(other.arrSize),writeInd(other.writeInd),readInd(other.readInd),lastActionIsWrite(other.lastActionIsWrite)
    {
        
        dataArr = new DATA[arrSize];
        for(size_t i = 0 ; i < arrSize; i ++)
           dataArr[i] =  other.dataArr[i]; 
        std::cout << "copy-ctor done" << std::endl;
    }
    ~CircularQueue()
    {
        //clear all the items in the array
        /*for (size_t i = 0; i < arrSize; ++i)
            delete dataArr[i];*/

        //delete the array itself        
        delete [] dataArr;        
        
        std::cout << "dtor done" << std::endl;
    }

        // other public functions
    DATA * top()
    {
        handleEnpty(true);
        DATA * pItem = new DATA(dataArr[readInd]);
        return pItem;
    }

    void insert(const DATA item)
    {
        handleNoFreeSpace(true);
        dataArr[writeInd] = item;
        writeInd = (writeInd+1) % arrSize;
        lastActionIsWrite = true;
    }
     
    DATA * pop()
    {
        DATA * retVal = top();
        readInd = (readInd+1) % arrSize;
        lastActionIsWrite = false;
        return retVal;
    }

    bool empty()
    {
        return handleEnpty(false);
    }

    bool full()
    {
        return handleNoFreeSpace(false);
    }

protected:
      bool handleNoFreeSpace(bool Throw = false)
      {
          bool hasProblem = ((writeInd) % arrSize == readInd % arrSize) && lastActionIsWrite;  
          //bool hasProblem = ( (writeInd+1) % arrSize == readInd % arrSize);
          //bool hasProblem = ( (readInd +1) % arrSize == writeInd % arrSize);
          if (hasProblem && Throw)
          {
              throw std::runtime_error(std::string("Failed: ") + "OutofBound");
              //throw Excpetion("OutofBound");
          }

          return hasProblem;
      }

      bool handleEnpty(bool Throw = false) {
          bool hasProblem = ((writeInd) % arrSize == readInd % arrSize) && !lastActionIsWrite;  
          //bool hasProblem = ( (writeInd+1) % arrSize == readInd % arrSize);
          //bool hasProblem = ( (readInd +1) % arrSize == writeInd % arrSize);
          if (hasProblem && Throw)
          {
              throw std::runtime_error(std::string("Failed: ") + "empty!");
              //throw Excpetion("OutofBound");
          }

          return hasProblem;
      }
};


void printArr(CircularQueue& arr) {
    
    //for(size_t i = 0 ; i < arr.arrSize; i++)
    while(!arr.empty())
    {
        DATA * item = arr.pop();
        std::cout << *item << " ";
    }
    std::cout << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    size_t size = 50;
    CircularQueue Arr(size);

    for(int i = 0; i < size; ++i )
    {
        Arr.insert(i+1);
    }
    /*Arr.insert(100);
    Arr.insert(99);*/


   
    //error
    for(int i = 0 ; i < 100; i++)
    {
        DATA* item1 = Arr.pop();
        DATA* item2 = Arr.pop();
        Arr.insert(*item1);
        Arr.insert(*item2);
    }
    // Sleep(1000);

    printArr(Arr);
    //Sleep(5000); 
    
	return 0;
}

