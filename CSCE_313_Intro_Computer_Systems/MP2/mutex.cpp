//Jason Gilman
//126006979


#include "mutex.hpp"

using namespace std;

Mutex::Mutex()
{
	m = PTHREAD_MUTEX_INITIALIZER; 
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m);
}

void Mutex::Lock()
{
	/*
	if(pthread_mutex_lock(&m) != 0)
	{
		throw "thread cannot be locked";
	}
	*/
	pthread_mutex_lock(&m);
}

void Mutex::Unlock()
{
	/*
	if(pthread_mutex_unlock(&m) != 0)
	{
		throw "thread cannot be unlocked";
	}
	*/
	pthread_mutex_unlock(&m);
}
