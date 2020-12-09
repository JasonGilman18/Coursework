#if !defined(DequeA_h)    /* To prevent problems from multiple inclusions */
#define DequeA_h

#include "DequeException.h"
//const int MAX_DEQUE = 10;    // maximum-size-of-list

using namespace std;

typedef int Type;


class Deque
{
	enum { DEF_CAPACITY = 100 };	// default deque capacity
private:
	Type* items;  	// array of deque items
	int capacity;	// deque capacity
	int n;  	// number of items in the deque
	int f, b;  	// indices to front and back, respectively

public:
   Deque(int);   // Constructor

   ~Deque(void);  // Destructor

   bool empty(void) const; // Determines whether a deque is empty.

   int size(void) const; 	// Determines the number of items in a deque.

   Type front(void) const throw(DequeException);

   Type back(void) const throw(DequeException);

   void insertFront(Type o) throw(DequeException);

   void insertBack(Type o) throw(DequeException);

   Type removeFront(void) throw(DequeException);

   Type removeBack(void) throw(DequeException);
};

#endif