//Jason Gilman

#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(int s)
{
	size = s;
	empty = Semaphore(size);
	full = Semaphore(0);
	mutex = Semaphore(1);
}

Buffer::~Buffer()
{
}

void Buffer::add(Request r)
{
	empty.P();
	mutex.P();
	//add
	list.push(r);
	mutex.V();
	full.V();
}

Request Buffer::remove()
{
	full.P();
	mutex.P();
	//remove
	Request ret = list.front();
	list.pop();
	mutex.V();
	empty.V();
	return ret;
}