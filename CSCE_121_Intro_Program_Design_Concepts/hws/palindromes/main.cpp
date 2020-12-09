#include <string>
#include <iostream>
#include "functions.h"
using namespace std;

int main(int argc, char *argv[]) //number of inputs, array of inputs
{
	if(argc == 1)
	{
		printUsageInfo(argv[0]);
		return 0;
	}
	else
	{
		bool caseSensitive = false;
		bool ignoreSpaces = true;
		bool called = false;
		for(int i=1;i<argc;++i)
		{
			string temp = (string)argv[i];
			if(temp.substr(0,1) == "-") //if its a flag
			{
				if(temp.length() == 2)
				{
					char letter = tolower((char)temp[1]);
					if(letter == 'c')
						caseSensitive = true;
					else if(letter == 's')
						ignoreSpaces = false;
					else
						printUsageInfo(argv[0]);
				}
				else if(temp.length() == 3)
				{
					string letters = temp.substr(1,3);
					if(letters == "cs" || letters == "Cs" || letters == "CS" || letters == "cS")
					{
						caseSensitive = true;
						ignoreSpaces = false;
					}
					else if(letters == "sc" || letters == "Sc" || letters == "SC" || letters == "sC")
					{
						caseSensitive = true;
						ignoreSpaces = false;
					}
					else
						printUsageInfo(argv[0]);
				}
			}
			else //its not a flag
			{
				called = true;
				bool yeah = isPalindrome(temp,caseSensitive,ignoreSpaces);
				if(yeah)
					cout << "\"" << argv[i] << "\"" << " is a palindrome." << endl;
				else
					cout << "\"" << argv[i] << "\"" << " is not a palindrome." << endl;
			}
		}
		if(!called)
			printUsageInfo(argv[0]);
	}
	return 0;
}