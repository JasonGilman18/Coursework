//Jason Gilman

#ifndef BUFFER_H
#define BUFFER_H

#include "Semaphore.hpp"
#include "Request.hpp"
#include <string>
#include <queue>

class Buffer
{
	private:
		Semaphore empty;
		Semaphore full;
		Semaphore mutex;
		std::queue<Request> list;
		int size;
	
	public:
		Buffer(int s);
		~Buffer();
		void add(Request r);
		Request remove();	
};

#endif