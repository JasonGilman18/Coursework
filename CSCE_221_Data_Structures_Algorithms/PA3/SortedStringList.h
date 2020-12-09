// SortedStringList.h  -- Header file for ADT SortedList (Pointer-based implementation)
// Revised 2019-02-14


#include <string>
using namespace std;

// Must define ListItemType before compilation
typedef string ListItemType;

class SortedStringList
{
public:
    SortedStringList(); 				// constructor

	bool isEmpty() const; 				// Returns true is the list is empty
	int size() const;					// Returns the number of items in the list
	void add(ListItemType newItem);		// Inserts newItem into its proper position in a sorted list.
	void remove(int position); 			// Removes the item at position index of a sorted list,
										//      if 1 <= index <= size(); otherwise, throws an exception
	void removeAll();					// Removes all the items in the list.
	void get(int position, ListItemType& s) const; // Retrieves the item at position index of a sorted list,
											// if 1 <= index <= size(); otherwise, throws an exception
	int locateIndex(ListItemType item)	const; // Returns the position where the item belongs or exists in a sorted list.
	
	void display() const;
	
private:
	struct DListNode 		// a node on the list
	{
		ListItemType item; 	// a data item on the list
		DListNode *prev;		// pointer to previous node
		DListNode *next;		// pointer to next node
	}; // end struct

   int numItems; 			// number of items in list
   DListNode *header;		// pointer to the header node of the linked list 
   DListNode *trailer;		// pointer to the trailer node of the linked list

   DListNode *find(int index) const;
   // Returns a pointer to the index-th node
   // in the linked list. Thows exception on invalid index
};

// End of header file.
