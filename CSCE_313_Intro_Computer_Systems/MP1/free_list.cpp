/* 
    File: free_list.cpp

    Author: Jason Gilman
            Department of Computer Science
            Texas A&M University
    Date  : 09/12/2109

    Modified: 

    This file contains the implementation of the class FreeList.

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include "free_list.hpp"
#include<cassert>

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
/* FUNCTIONS FOR CLASS SegmentHeader */
/*--------------------------------------------------------------------------*/

SegmentHeader::SegmentHeader(size_t _length, bool _is_free) {
  length = _length;
  is_free = _is_free;
  cookie = COOKIE_VALUE;
  // You may need to initialize more members here!
  next = nullptr;
  prev = nullptr;
}

SegmentHeader::~SegmentHeader() {
  // You may need to add code here.
}


void SegmentHeader::CheckValid() {
  if (cookie != COOKIE_VALUE) {
    cout << "INVALID SEGMENT HEADER!!" << endl;
    assert(false);
    // You will need to check with the debugger to see how we got into this
    // predicament.
  }
}

size_t SegmentHeader::getLength()
{
	return length;
}
  
bool SegmentHeader::getFree()
{
	return is_free;
}
  
SegmentHeader* SegmentHeader::getPrev()
{
	return prev;
}
  
SegmentHeader* SegmentHeader::getNext()
{
	return next;
}

void SegmentHeader::setPrev(SegmentHeader* s)
{
	prev = s;
}

void SegmentHeader::setNext(SegmentHeader* s)
{
	next = s;
}
  
void SegmentHeader::setFree(bool b)
{
	is_free = b;
}
  
void SegmentHeader::setLength(size_t s)
{
	length = s;
}

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR CLASS FreeList */
/*--------------------------------------------------------------------------*/

FreeList::FreeList(size_t b) {
  // You will need to add code here!
  
  head = NULL;
  blockSize = b;
}

FreeList::~FreeList() {
  // You may need to add code here.
}

bool FreeList::Add(SegmentHeader * _segment) {
  
  if(head == NULL)
  {
	  head = _segment;
	  char* p = (char*)_segment;
	  cout << "0: head created, " << p <<endl;
  }
  else if(head->getNext() == nullptr)
  {
	  head->setNext(_segment);
	  _segment->setPrev(head);
	  cout << "1: second space added" << endl;
  }
  else
  {
	  SegmentHeader* temp = head;
	  
	  while(temp->getNext() != nullptr)
		  temp = temp->getNext();
	  
	  temp->setNext(_segment);
	  _segment->setPrev(temp);
	  cout << "2"<<endl;
  }
  return true;
}

bool FreeList::Remove(SegmentHeader * _segment) {
  
  SegmentHeader* temp = head;
  if(temp == NULL)
	  return false;
  else if(temp == _segment)		//issue if there is one node
  {
	  if(temp->getNext() == nullptr)
	  {
		  head = NULL;
		  cout << "removed here" << endl;
		  return true;
	  }
	  else
	  {
		head = temp->getNext();
		head->setPrev(nullptr);
		cout << "remove: head" << endl;
		return true;
	  }
  }
  else
  {
	  while(temp->getNext() != nullptr && temp != _segment)
		  temp = temp->getNext();
	  
	  if(temp != _segment)
	  {
		  cout << "remove not in here" << endl;
		  return false;
	  }
	  else
	  {
		if(temp->getNext() == nullptr)
		{
			temp->getPrev()->setNext(nullptr);
			cout << "remove: tail" << endl;
			return true;
		}
		else
		{
			temp->getPrev()->setNext(temp->getNext());
			temp->getNext()->setPrev(temp->getPrev());
			cout << "remove: middle" << endl;
			return true;
		}
	  }
  }
  
}

SegmentHeader* FreeList::Search(size_t _length)
{
	SegmentHeader* temp = head;
	if(temp->getNext() == nullptr)
	{
		if(temp->getFree())
			if(temp->getLength() >= _length)
			{
				cout << "search: head" << endl;
				return temp;
			}
	}
	else
	{
		while(temp->getNext() != nullptr)			//issue if there is 2 nodes only in free list.
		{
			if(temp->getFree())
				if(temp->getLength() > _length)
				{
					cout << "search: other" << endl;
					return temp;
				}
			temp = temp->getNext();
		}
		return nullptr;
	}
	
}

SegmentHeader* FreeList::getHead()
{
	return head;
}
