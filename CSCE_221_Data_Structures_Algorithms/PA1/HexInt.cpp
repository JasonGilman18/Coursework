#include "HexInt.h"
#include <iostream>
using namespace std;


int convert(char c)
{
	//convert hexadecimal to int, so A = 10 B = 11 1 = 1 5 = 5 etc
	
	switch(c)
	{
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		case '9' : return 9;
		case 'A' : return 10;
		case 'B' : return 11;
		case 'C' : return 12;
		case 'D' : return 13;
		case 'E' : return 14;
		case 'F' : return 15;
		case 'G' : return 16;
	}
}

string convertBack(int i)
{
	//convert int like 11 15 16 to hex so B F G 
	switch(i)
	{
		case 0 : return "0";
		case 1 : return "1";
		case 2 : return "2";
		case 3 : return "3";
		case 4 : return "4";
		case 5 : return "5";
		case 6 : return "6";
		case 7 : return "7";
		case 8 : return "8";
		case 9 : return "9";
		case 10 : return "A";
		case 11 : return "B";
		case 12 : return "C";
		case 13 : return "D";
		case 14 : return "E";
		case 15 : return "F";
		case 16 : return "G";
	}
}



HexInt::HexInt(const char* str)
{
	//initialize array of size same as incoming string
	//for loop through string
	//use convert helper method to change each digit
	//fill array [1,2,11,15,3,16]
	//will the right most digit in hexadec be the last index

	int array[strlen(str)];
	for(int i=0;i<strlen(str);++i)
	{
		array[i] = str[i];
	}
}


HexInt::~HexInt()
{
	
}


char* HexInt::toString()
{
	string s = string(((char*)array));
	int length = s.length()-20;
	for(int i=0;i<length;++i)
		s.insert(0,"0");
	return (char*)(s.c_str());
}


char* HexInt::toTrimmedString()
{
	return (char*)array;
}


HexInt* HexInt::add(HexInt& lhs, HexInt& rhs)
{	
	string output = "";
	HexInt shortOne = lhs;
	HexInt longOne = rhs;
	int left = (sizeof(lhs.array)/sizeof(*lhs.array));
	int right = (sizeof(rhs.array)/sizeof(*rhs.array));
	if(left > right)
	{
		shortOne = rhs;
		longOne = lhs;
	}
	else if(left < right)
	{
		longOne = rhs;
		shortOne = lhs;
	}
	else
	{
		shortOne = rhs;
		longOne = lhs;
	}
	
	int sum = 0;
	int carry = 0;
	int remainder = 0;
	int longSize = (sizeof(longOne.array)/sizeof(*longOne.array));
	int shortSize = (sizeof(shortOne.array)/sizeof(*shortOne.array));
	int help = longSize - shortSize;//when access longOne add this.
	for(int i=shortSize-1;i>=0;--i)
	{
		sum = convert(shortOne.array[i]) + convert(longOne.array[i+help]) + carry;
		cout << to_string(sum) << endl;
		carry = sum/16;
		remainder = sum%16;
		output.insert(0,convertBack(remainder));
		sum = 0;
		remainder = 0;
	}
	
	//get the rest from the long string
	//cout << output<< endl;
	for(int i=(longSize - shortSize)-1;i>=0;--i)
	{
		output.insert(0,convertBack(convert(longOne.array[i])));
	}
	
	//output is in string form. nees hexInt object.
	
	
	
	return new HexInt(output.c_str());
}



