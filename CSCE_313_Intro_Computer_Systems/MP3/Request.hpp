//Jason Gilman

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

class Request
{
	private:
		string data;
		int id;
		int c;
	
	public:	
		Request(string s, int i, int co);
		void setData(string d);
		void setID(int i);
		void setCount(int co);
		string getData();
		int getID();
		int getCount();
};

#endif