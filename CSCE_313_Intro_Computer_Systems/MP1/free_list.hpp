/* 
    File: free_list.hpp

    Author: Jason Gilman
            Department of Computer Science and Engineering
            Texas A&M University
    Date  : 09/15/2019

    Modified:

*/

#ifndef _free_list_hpp_                   // include file only once
#define _free_list_hpp_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cstdlib>
#include <cassert>


/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

class SegmentHeader {

private:

  static const unsigned COOKIE_VALUE = 0xBAAB00;
  unsigned int cookie; /* To check whether this is a genuine header! */
  size_t length;
  bool is_free;
	SegmentHeader* prev;
	SegmentHeader* next;
  // You will need additional data here!
  
  
public:
  
  SegmentHeader(size_t _length, bool _is_free = true);
  
  ~SegmentHeader();
  /* We probably won't need the destructor. */

  void CheckValid();
  /* Check if the cookie is valid. */
  
  size_t getLength();
  /*gets length private data member of SH*/
  
  bool getFree();
  /*gets if the SH is free*/
  
  SegmentHeader* getPrev();
  /*gets the previous pointer of the SH*/
  
  SegmentHeader* getNext();
  /*gets the next pointer of the SH*/
  
  void setPrev(SegmentHeader* s);
  /*sets the prev pointer of the SH*/

  void setNext(SegmentHeader* s);
  /*sets the next pointer of the SH*/
  
  void setFree(bool b);
  /*sets the is_free value for the SH*/
  
  void setLength(size_t s);
  /*sets the length of the SH*/
  
};

/*--------------------------------------------------------------------------*/
/* FORWARDS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS  FreeList */
/*--------------------------------------------------------------------------*/

class FreeList {

 private:

  /* Here you add whatever private members you need...*/
  SegmentHeader* head;
  size_t blockSize;

public:

  FreeList(size_t b); 
  /* This function initializes a new free-list. */

  ~FreeList(); 
  /* We probably don't need a destructor. */ 

  bool Remove(SegmentHeader * _segment); 
  /* Remove the given segment from the given free list. 
     Returns true if the function succeeds.
  */ 

  bool Add(SegmentHeader * _segment); 
  /* Add the segment to the given free list. */
  
  SegmentHeader* Search(size_t _length);
  /* searches the free list for the first segment that is large enough and is free. */
  
  SegmentHeader* getHead();
  /* returns the head pointer of the list*/
  
};

#endif 
