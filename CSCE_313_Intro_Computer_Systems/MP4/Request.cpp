//Jason Gilman

#include "Request.hpp"

using namespace std;

Request::Request(string s, int i, int co)
{
	data = s;
	id = i;
	c = co;
}

void Request::setData(string d)
{
	data = d;
}

void Request::setID(int i)
{
	id = i;
}

void Request::setCount(int co)
{
	c = co;
}

string Request::getData()
{
	return data;
}

int Request::getID()
{
	return id;
}

int Request::getCount()
{
	return c;
}
