//Jason Gilman
//126006979

#include "mutex_guard.hpp"

using namespace std;

MutexGuard::MutexGuard(Mutex &p)
{
	m = &p;
	m->Lock();
}

MutexGuard::~MutexGuard()
{
	m->Unlock();
}