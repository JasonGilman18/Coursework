// ListDemo.cpp  -- Short program to exercise a SortedStringList Implementation
// This program does not assume a particular implementation 
// (e.g. array, vector, singly- or doubly-linked list...) 
// Revised 2019-02-14

#include <iostream>
using namespace std;

#include <string>
#include "SortedStringList.h"
void printList(SortedStringList);

int main(int argc, char *argv[])
{
	SortedStringList myGroceryList;
	string s;
	
	myGroceryList.add("apples");
	myGroceryList.add("butter");
	myGroceryList.add("coconut");
	myGroceryList.add("pecans");
	myGroceryList.add("eggs");
	myGroceryList.add("bread");
	myGroceryList.add("chicken");
	myGroceryList.add("rice");
	myGroceryList.add("red beans");
	myGroceryList.add("sausage");
	myGroceryList.add("flour");
	myGroceryList.add("cheese");
	myGroceryList.add("allspice");
	myGroceryList.add("tofu");
	myGroceryList.add("bamboo shoots");

	//print out original List
	cout << "Grocery List" << endl;
	printList(myGroceryList); 

	// test remove()
	cout << "Grocery List after removing bread" << endl;
	int pos = myGroceryList.locateIndex("bread");
	string dataItem;
	myGroceryList.get(pos, dataItem);
    if (dataItem.compare("bread") == 0)
	{
		cout << "bread is present, will be removed" << endl;
		myGroceryList.remove(pos);
	}
	else
		cout << "bread not found" << endl;
	printList(myGroceryList); 
	
	// test removeAll()
	cout << "Grocery List after removing all items" << endl;
	myGroceryList.removeAll();	
	printList(myGroceryList); 
	
	// this will throw an exception and abort the program
	cout << "Accessing an invalid list item should throw an exception" << endl;
	myGroceryList.remove(4);

	return 0;
}

// a function to print out a list
void printList(SortedStringList list)
{
	cout << "The list has " << list.size() << " entries." << endl;
	for (int index = 1; index <= list.size(); index++)
	{
		string str;
		list.get(index, str);
		cout << index << ". " << str << endl;
	}
}
