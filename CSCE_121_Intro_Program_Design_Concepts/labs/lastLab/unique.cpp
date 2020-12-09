#include "unique.h"
using namespace std;

template <class UniquePtr>

UniquePtr::UniquePtr(T val)
{
	holder = *val;
}

UniquePtr::~UniquePtr()
{
	delete holder;
}

T& UniquePtr::operator*()
{
	return &*holder;
}

UniquePtr& UniquePtr::operator->()
{
	return *this;
}