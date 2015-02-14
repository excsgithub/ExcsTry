// CircularQueue.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <windows.h> 

#include "stdafx.h"
#include "string"
#include <stdexcept>

//typedef int DATA; 
typedef double DATA; 
template <typename T>
class CircularQueueTemplate
{
   

public:
    size_t arrSize;

protected:
    size_t writeInd;
    size_t readInd;
    bool lastActionIsWrite;
    //bool wasLastWrite;

    T * dataArr;

public: //  CTOR DTOR functions

    //template <typename T>
    CircularQueueTemplate(size_t size):arrSize(size),writeInd(0),readInd(0),lastActionIsWrite(false)
    {
        dataArr = new T[arrSize];
        std::cout << "ctor done" << std::endl;
    }

    //template <typename T>
    CircularQueueTemplate(CircularQueueTemplate & other):arrSize(other.arrSize),writeInd(other.writeInd),readInd(other.readInd),lastActionIsWrite(other.lastActionIsWrite)
    {
        
        dataArr = new T[arrSize];
        for(size_t i = 0 ; i < arrSize; i ++)
           dataArr[i] =  other.dataArr[i]; 
        std::cout << "copy-ctor done" << std::endl;
    }

    
    ~CircularQueueTemplate()
    {
        //clear all the items in the array
        /*for (size_t i = 0; i < arrSize; ++i)
            delete dataArr[i];*/

        //delete the array itself        
        delete [] dataArr;        
        
        std::cout << "dtor done" << std::endl;
    }

    //------------- other public functions
   
    T * top()
    {
        handleEnpty(true);
        T * pItem = new T(dataArr[readInd]);
        return pItem;
    }

    
    void insert(const T item)
    {
        handleNoFreeSpace(true);
        dataArr[writeInd] = item;
        writeInd = (writeInd+1) % arrSize;
        lastActionIsWrite = true;
    }
    
    
    T * pop()
    {
        T * retVal = top();
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

    // remove all the content of the queqe
    void flash() {
        writeInd = readInd = 0;
        lastActionIsWrite = false;
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

template <typename T>
void printArrRemover(CircularQueueTemplate<T>& arr) {
    
    //for(size_t i = 0 ; i < arr.arrSize; i++)
    while(!arr.empty())
    {
        T * item = arr.pop();
        std::cout << *item << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void printArr(CircularQueueTemplate<T> arr) {
    printArrRemover(arr);    
}


int _tmain(int argc, _TCHAR* argv[])
{
    size_t size = 50 ;
    CircularQueueTemplate<DATA> Arr(size);

    for(size_t i = 0; i < size / 2; ++i )
    {
        Arr.insert((i+1) + 0.001);
    }
    /*Arr.insert(100);
    Arr.insert(99);*/


   
    
    for(int i = 0 ; i < 100; i++)
    {
        DATA* item1 = Arr.pop();
        DATA* item2 = Arr.pop();
        Arr.insert(*item2);
        Arr.insert(*item1);
    }

    while (!Arr.full())
        Arr.insert(-1);
        
    std::cout << "call printArr: (with copy)" <<  std::endl;
    printArr(Arr);
    CircularQueueTemplate<DATA> ArrCopy(Arr);
    std::cout << "is empty?: " << Arr.empty() << std::endl;
    std::cout << "call printArrRemover: " <<  std::endl;
    printArrRemover(Arr);
    std::cout << "is empty?: " << Arr.empty() << std::endl;

    std::cout << "call printArr: on ArrCopy" <<  std::endl;
    printArr(ArrCopy);
    std::cout << "call flash" <<  std::endl;
    ArrCopy.flash();
    std::cout << "call printArr: on ArrCopy" <<  std::endl;
    printArr(ArrCopy);
    std::cout << "ArrCopy is empty?: " << ArrCopy.empty() << std::endl;
        
    return 0;

    /*                         -----------OUTPUT-----------
    ctor done
    call printArr: (with copy)
    copy-ctor done
    19.001 10.001 21.001 12.001 23.001 14.001 25.001 16.001 1.001 18.001 3.001 20.00
    1 5.001 22.001 7.001 24.001 9.001 2.001 11.001 4.001 13.001 6.001 15.001 8.001 1
    7.001 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1

    dtor done
    copy-ctor done
    is empty?: 0
    call printArrRemover:
    19.001 10.001 21.001 12.001 23.001 14.001 25.001 16.001 1.001 18.001 3.001 20.00
    1 5.001 22.001 7.001 24.001 9.001 2.001 11.001 4.001 13.001 6.001 15.001 8.001 1
    7.001 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1

    is empty?: 1
    call printArr: on ArrCopy
    copy-ctor done
    19.001 10.001 21.001 12.001 23.001 14.001 25.001 16.001 1.001 18.001 3.001 20.00
    1 5.001 22.001 7.001 24.001 9.001 2.001 11.001 4.001 13.001 6.001 15.001 8.001 1
    7.001 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1

    dtor done
    call flash
    call printArr: on ArrCopy
    copy-ctor done

    dtor done
    ArrCopy is empty?: 1
    dtor done
    dtor done
    */
}

