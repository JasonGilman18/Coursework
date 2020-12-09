#include <string>
#include <fstream>
#include <iostream>
#include "HexInt.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		return 1;
	}
	// Open the input and output
	
	ifstream inputFile;
	inputFile.open(argv[1]);
	ofstream outputFile;
	outputFile.open(argv[2]);
	
	
	string line;
	string lhs;
	string rhs;
	if(inputFile.is_open())
	{
		while(getline(inputFile,line))
		{ 
			for(int i=0;i<line.length()-1;++i)
			{
				if(line.at(i) == '+')
				{
					lhs = line.substr(0,i);
					rhs = line.substr(i+1,line.length()-1);
				}
			}
			rhs.pop_back();
			
			//construct HexInts
			//add the two objects
			//output result to a file
			HexInt l =  HexInt(lhs.c_str());
			HexInt r = HexInt(rhs.c_str());
			HexInt* result = HexInt::add(l,r);
			outputFile << result << endl;
		}
	}
	
	//clost output and input
	inputFile.close();
	outputFile.close();
	
	return 0;
}
