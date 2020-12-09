#ifndef HEXINT_H
#define HEXINT_H
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
//simple class setup
class HexInt
{
	public:
		HexInt(const char* str);
		~HexInt();
		char* toString();
		char* toTrimmedString();
		static HexInt* add(HexInt& lhs, HexInt& rhs);
	
	private:
		 unsigned char array[];
	
};
#endif

