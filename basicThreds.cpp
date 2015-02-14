// chat_threads.cpp : Defines the entry point for the console application.
//

//-------------------this verion is with threads-----------------------

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <ostream>
#include <fstream>
//need vs2012+
	//#include <thread>
	//#include <pthread.h>

//for threads in 2010
	#include <windows.h> 
	#include <process.h>


//===========================================================
const int INT_saveToFile = 1000 * 7;
const int INT_print = 1000 * 5;

// message DB
std::vector<std::string> messageDB;  

//outfile on disk
std::ofstream file("c:\\temp\\chatTestMessages.log",std::ofstream::out | std::ofstream::app);  

//total message got from user
int messageCounter = 0;

//last message that was saved to disk
int lastSaved = 0;

//should thread quit his main function - not realy needed at the end
bool shouldDie = false;

//mutex for "save" "print"
HANDLE ghMutex = CreateMutex( NULL, FALSE, NULL); 

//the thread that do the save & print
HANDLE t1; // the thread

bool isQuit(const std::string & inStr);
void saveDB(int ind);

bool isQuit(const std::string & inStr) {
	std::string tmp = inStr;
	std::transform(tmp.begin(), tmp.end(),tmp.begin(), ::tolower);
	return (tmp.compare("quit") == 0) || (tmp.compare("x") == 0) || (tmp.compare("q") == 0);
}

void saveDB(int ind) {
	std::cout << "---- saving" << std::endl;
	for(unsigned int i=ind; i<messageDB.size(); i++)    
     file << messageDB[i] << std::endl;
}

void printDB(int ind) {
	WaitForSingleObject(ghMutex, INFINITE);
	for(unsigned int i = ind; i < messageDB.size(); i++) {
		std::cout << "[" << i << "] " << messageDB[i] << std::endl;
	}
	ReleaseMutex(ghMutex);

}

void test_putMessagesInDB() {
	messageDB.push_back("hi");
	messageDB.push_back("my name");
	messageDB.push_back("is Da");
}

int 
gcd ( int a, int b )
{
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

void saveLogic() {
	//call lock here
	WaitForSingleObject(ghMutex, INFINITE);
	saveDB(lastSaved);
	lastSaved = messageCounter;
	ReleaseMutex(ghMutex);
}

void handleDie()
{	
	if (shouldDie)
	{	
		std::cout << "killing thread.." << std::endl;
		TerminateThread(t1, 0);
	}			
}

void  printAndSaveThread( void *arg ) {
	int step = gcd(INT_print,INT_saveToFile);
	int counter = 0;
	int maxInt = max(INT_print,INT_saveToFile);
	int minInt = min(INT_print,INT_saveToFile);
	while(!shouldDie)
	{
		while(counter < maxInt)
		{
			handleDie();
			Sleep( step );		
			counter+= step;

			if ((counter % minInt) == 0 )
				printDB ((int)(arg));
		}
		counter = 0;
		handleDie();
		saveLogic();
	}
	//std::cout << "I am dead thread.." << std::endl;
}
//===========================================================


int _tmain(int argc, _TCHAR* argv[])
{
	//uintptr_t t1 =  _beginthread( printAndSaveThread, 0, (void*)0 );
	t1 =  (HANDLE) _beginthread( printAndSaveThread, 0, (void*)0 );
	std::cout << "instractions: q for quit, p for print, save for save messages manualy, please write messages:\n";
	std::cout << "keep writing input messages:\n"  
			  << "----------------------------" << std::endl;
	std::string message;
	//test_putMessagesInDB();
	do 
	{
		std::getline(std::cin,message);
		if (message.compare("print") == 0 || message.compare("p") == 0) {
			printDB(0);
		} else if( message.compare("save") == 0) {
			//saveDB(lastSaved);
			//lastSaved = messageCounter;
			saveLogic();
		} else 	if(isQuit(message)) {
			break;
		} else {
			messageDB.push_back(message);
			messageCounter++;
		}			
		
	} while (true);	

	shouldDie = true;
	std::cout << "\nlast save before quiting..." << std::endl; 
	saveLogic();
	std::cout << "\nleting the tread update and die..." << std::endl; 
	
	
	handleDie();
	Sleep(1);	
	WaitForSingleObject(t1, INFINITE);
	std::cout << "\nthread not running - you are done!" << std::endl;  
	file.close();


	//t1
	return 0;
}



//-------------------------------------------------------
