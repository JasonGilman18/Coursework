#include <string>
#include <cmath>
#include <iostream>
#include "functions.h"
using namespace std;

void printUsageInfo(std::string s)
{
	cout << "Usage: " << s << " [-c] [-s] string ..." << endl;
	cout << "  -c: turn on case sensitivity" << endl;
	cout << "  -s: turn off ignoring spaces";
}

bool isPalindrome(std::string s, bool caseSense, bool ignoreSpaces)
{
	string pre = preprocessString(s,ignoreSpaces);
	if(!caseSense)
	{
		for(int i=0;i<pre.length();++i)
		{
			pre[i] = tolower(pre[i]);
		}
	}
	return isPalindromeR(pre);
}

//helper functions
std::string preprocessString(std::string s, bool ignoreSpaces)
{
	if(ignoreSpaces)
	{
		for(int i=0;i<s.length();++i)
		{
			char c = (char)s.at(i);
			if(!isalnum(c))
			{
				s.erase(i,1);
				i -= 1;
			}
		}
	}
	else
	{
		for(int i=0;i<s.length();++i)
		{
			char c = (char)s.at(i);
			if(!isalnum(c) && c != ' ')
			{
				s.erase(i,1);
				i -= 1;
			}
		}
	}
	
	return s;
}

bool isPalindromeR(std::string s)
{
	if(s.length() == 0 || s.length() == 1)
		return true;
	else if(s[0] == s[s.length()-1])
	{
		s.erase(s.length()-1,1);
		s.erase(0,1);
		return isPalindromeR(s);
	}
	else
		return false;
}
