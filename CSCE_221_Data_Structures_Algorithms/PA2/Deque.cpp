#include "Deque.h"
#include <cstddef>



   Deque::Deque(int cap)       // constructor from capacity
   {
	   capacity = cap;
	   items = new Type[capacity];
	   n = 0;
	   f = 0;
	   b = capacity - 1;
   }

   Deque::~Deque()		// destructor
   {
		delete [] items;
   }

   bool Deque::empty() const     // is the deque empty?
   {
	   return n == 0;
   }

   int Deque::size() const	// number of items in the deque
   {
	   return n;
   }

   Type Deque::front() const throw(DequeException)
   {
	   if(n==0)
		   throw DequeException("Empty Array");
	   else
		   return items[f];
   }

   Type Deque::back() const throw(DequeException)
   {
	   if(n==0)
		   throw DequeException("Empty Array");
	   else
		   return items[b];
   }

   void Deque::insertFront(Type o) throw(DequeException)
   {
	   if(n==capacity)
	   {
		   throw DequeException("Full Array");
	   }
	   else if(n==0)
	   {
		   items[0] = o;
		   f = 0;
		   b = 0;
		   ++n;
	   }
	   else
	   {
		   items[f+1] = o;
		   ++f;
		   ++n;
	   }
   }

   void Deque::insertBack(Type o) throw(DequeException)
   {
	   if(n==capacity)
	   {
		   throw DequeException("Full Array");
	   }
	   else if(n==0)
	   {
		   items[0] = o;
		   f = 0;
		   b = 0;
		   ++n;
	   }
	   else if(b==0)
	   {
		   items[capacity-1] = o;
		   b = capacity-1;
		   ++n;
	   }
	   else
	   {
		   items[b-1] = o;
		   --b;
		   ++n;
	   }
   }

   Type Deque::removeFront() throw(DequeException)
   {
	   int temp;
	   if(n==0)
	   {
		 throw DequeException("Empty Array");
	   }
	   if(n==1)
	   { 
		   temp = f;
		   n=0;
		   f = 0;
		   b = capacity-1;
		   return items[temp];
	   }
	   else
	   {
		   temp = f;
			--n;
			--f;
			return items[temp];
	   }
   }

   Type Deque::removeBack() throw(DequeException)
   {
	   int temp;
	   if(n==0)
	   {
		 throw DequeException("Empty Array");
	   }
	   else if(n==1)
	   { 
		   temp = b;
		   n=0;
		   f = 0;
		   b = capacity-1;
		   return items[temp];
	   }
	   else if(b==capacity-1)
	   {
		   temp = b;
		   --n;
		   b = 0;
		   return items[temp];
	   }
	   else
	   {
		   temp = b;
			--n;
			++b;
			return items[temp];
	   }
   }