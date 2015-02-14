// trim_string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

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


void revarseChars(std::string& refResult)
{
	std::string result;
	std::size_t all = refResult.size();
	for(int i = 0; i < refResult.size() ; i++)
	{
		result+= refResult[all-1-i];
	}

	refResult = result;
}


void splitStringAdv(std::vector<std::string> & outVec, const std::string & inputStr)
{
	//vector<string> tokens;
	std::istringstream iss(inputStr);
	std::copy(std::istream_iterator<std::string>(iss),
     std::istream_iterator<std::string>(),
     std::back_inserter(outVec));
}

void splitString(std::vector<std::string> & outVec, const std::string & inputStr)
{
	std::string word;

	for(int i = 0; i < inputStr.size(); i++) 	{
		if (!isspace(inputStr[i])) {
			word+=inputStr[i];
		}
		else {
			outVec.push_back(word);
			word = "";
		}
	}
	outVec.push_back(word);
}

void refResultWords(std::string& inputStr)
{
	std::string result;
	std::vector<std::string> outVec;
	splitString(outVec, inputStr);

	for(int i = 0; i < outVec.size(); i++)
	{
		revarseChars(outVec[i]);
		result += outVec[i] + " ";
	}

	inputStr = result;
}



void revarseString(std::string& refResult)
{
	revarseChars(refResult);
	refResultWords(refResult);
}




int _tmain(int argc, _TCHAR* argv[])
{
	std::string input = "hi my name     is david" ;

	std::string output;
	std::cout << "input: " << input << std::endl;
	
	output = input;
	revarseString(output);
	
	std::cout << std::endl;
	std::cout << "output:" << output << std::endl;
	
	
	//std::cout << std::endl;
	//output = input;
	//revarseChars(output);
	//std::cout << "revarseChars:" << output << std::endl;
	//
	//std::cout << std::endl;
	//output = input;
	//refResultWords(output);
	//std::cout << "refResultWords:" << output << std::endl;
	return 0;
}

