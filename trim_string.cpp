// trim_string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

#include <string>

void trimNoSpacesBest(std::string& refResult)
	{
		//std::cout << "test: " << remove_if(refResult.begin(), refResult.end(), isspace), refResult.end())‎ << std::endl;
		refResult.erase(remove_if(refResult.begin(), refResult.end(), isspace), refResult.end());		
	}

void trimNoSpaces(std::string& refResult)
{
	std::string result = "";

	for (int i = 0; i < refResult.size(); i++)
	{
		if (isspace(refResult[i]))
			continue;
		result+= refResult[i];
	}
	refResult = result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string input = "hi my name     is david" ;

	std::string output;
	std::cout << "input: " << input << std::endl;
	
	output = input;
	trimNoSpaces(output);
	
	std::cout << std::endl;
	std::cout << "output:" << output << std::endl;
	
	
	std::cout << std::endl;
	output = input;
	trimNoSpacesBest(output);
	std::cout << "o Best:" << output << std::endl;
	
	return 0;
}

