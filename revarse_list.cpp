// revarse_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	 // New list
    List list;

    // Append nodes to the list
    list.Append(100);
   // list.Print();
    list.Append(200);
   // list.Print();
    list.Append(300);
    //list.Print();
    list.Append(400);
    //list.Print();
    list.Append(500);
    list.Print();
	std::cout << "revarsing: ------ " << std::endl;
	list.Revarse();
	list.Print();
    //// Delete nodes from the list
    //list.Delete(400);
    //list.Print();
    //list.Delete(300);
    //list.Print();
    //list.Delete(200);
    //list.Print();
    //list.Delete(500);
    //list.Print();
    //list.Delete(100);
    //list.Print();

		return 0;
}



