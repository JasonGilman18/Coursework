#ifndef UNIQUE_H
#define UNIQUE_H

template <typename T>

class UniquePtr
{
	public:
		UniquePtr(T val);
		~UniquePtr();
		UniquePtr(const UniquePtr<T>& lhs);
		UniquePtr& operator=(const UniquePtr<T>& lhs);
		T& operator*();
		UniquePtr& operator->();
		
	private:
		T* holder;
		
};
#endif


template <typename T>
UniquePtr<T>::UniquePtr(T val)
{
	holder = new T(val);
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
	delete holder;
}

template <typename T>
T& UniquePtr<T>::operator*()
{
	return &*holder;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator->()
{
	return *this;
}