/* 
    File: my_allocator.cpp

    Author: Jason Gilman
            Department of Computer Science
            Texas A&M University
    Date  : 09/05/2019

    Modified: 

    This file contains the implementation of the class MyAllocator.

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cstdlib>
#include "my_allocator.hpp"
#include <assert.h>
#include <iostream>

/*--------------------------------------------------------------------------*/
/* NAME SPACES */ 
/*--------------------------------------------------------------------------*/

using namespace std;
/* I know, it's a bad habit, but this is a tiny program anyway... */

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR CLASS MyAllocator */
/*--------------------------------------------------------------------------*/

MyAllocator::MyAllocator(size_t _basic_block_size, size_t _size) {
  // We don't do anything yet...
  /*
  startAddress = malloc(_size);				//allocate memory of size _size; returns the start of the allocation as void*.
  remainingAddress = startAddress;			//create char* remainingAddress to compute artithmetic of how much space is left.
  remainingSize = _size;  					//remainingSize, the amount of memory left that was originally allocated
  */
  //list = FreeList();				//creates the free list, head is set to null
   
   
  startAddress = malloc(_size);				//gets the pointer to the start of the memory pool
  remainingAddress = startAddress;
  if(_size < _basic_block_size)
	_size = _basic_block_size;
	size_t fib = 0;
	int i = 1;
	while(fib < _size)
	{
		fib = Fibonacci(i)*_basic_block_size;
		FreeList n = FreeList(fib);
		SegmentHeader* newSH = new (startAddress)SegmentHeader(_size,true);
		n.Add(newSH);
		list.push_back(n);
		i++;
	}
 
  //SegmentHeader* newSH = new (startAddress)SegmentHeader(_size, true);	//creates SH at the start of memory pool, the size being the entire memory pool.
  //list.Add(newSH);							//add the SH to the free list, so the info can be accessed at a later time.
}

MyAllocator::~MyAllocator() {
  // Same here...
  
  free(startAddress);						//frees up the memory that was originally allocated in constructor.
  
}

Addr MyAllocator::Malloc(size_t _length) {
  
  /*
  if(_length <= remainingSize)							//if there is space left
  {
	  remainingSize = remainingSize - _length;	  		//subtract how much space you are about to use.
	  void* tempAddress = remainingAddress;				//allocate and update the begining of where the availible memory is.
	  remainingAddress = (char*)remainingAddress + _length;
	  return tempAddress;								//return where the start of availible memory is.														
  }
  else
	  return nullptr; 									//return null if there isnt space left.
  
  */
  //void* tempAddress = remainingAddress;
  
  
  
  
  
  /*
  SegmentHeader* CSeg = list.Search(_length + sizeof(SegmentHeader));			//cseg search list for correct place?
  list.Remove(CSeg);
  
  
  void* tempPointer = (char*)CSeg + sizeof(SegmentHeader) + _length;
  SegmentHeader* newCSeg = new (tempPointer)SegmentHeader((CSeg->getLength() - sizeof(SegmentHeader) - _length), true);
  
  CSeg->setLength(sizeof(SegmentHeader) + _length);
  CSeg->setFree(false);
  
  list.Add(CSeg);
  list.Add(newCSeg);
  
  return CSeg + sizeof(SegmentHeader);
  */
  
  for(int i=0;i<list.size();i++)
  {
	  
  }
  
  
  return sizeof(SegmentHeader);
}

bool MyAllocator::Free(Addr _a) {
  // This empty implementation just uses C standard library free
  //free(startAddress);
  //std::free(_a);
  
  SegmentHeader* fseg = (SegmentHeader*)((char*)_a - sizeof(SegmentHeader));
  fseg->setFree(true);
  list.Add(fseg);
  return true;
}

size_t MyAllocator::Fibonacci(int i)
{
	if(i <= 1)
		return (size_t)i;
	return size_t(Fibonacci(i-1) + Fibonacci(i-2));
}

