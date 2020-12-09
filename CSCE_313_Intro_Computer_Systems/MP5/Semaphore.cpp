//Jason Gilman
//126006979

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <unistd.h>

#include "Semaphore.hpp"

Semaphore::Semaphore()
{
	
}

Semaphore::Semaphore(int _val)
{
	m = PTHREAD_MUTEX_INITIALIZER;
	c = PTHREAD_COND_INITIALIZER;
	value = _val;
}

Semaphore::~Semaphore()
{
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
}

int Semaphore::P()
{
	pthread_mutex_lock(&m);
	while(value == 0)
		pthread_cond_wait(&c, &m);
	pthread_mutex_unlock(&m);
	value = value - 1;
	return value;
}

int Semaphore::V()
{
	pthread_mutex_lock(&m);
	value = value + 1;
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c);
	return value;
}