#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() 
{
	// Implement this function
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList() 
{
	// Implement this function
	Node* next = nullptr;
	while(head)
	{
		next = head->next;
		delete head;
		head = next;
	}
}

LinkedList::LinkedList(const LinkedList& source) 
{
	// Implement this function
	Node* next = nullptr;
	while(head)
	{
		next = head->next;
		delete head;
		head = next;
	}
	
	if(source.head != nullptr)
	{
		Node* sourceNode = source.head;
		head->data = sourceNode->data;
		sourceNode = sourceNode->next;
		Node* prev = head;
		while(sourceNode)
		{
			prev->next = new Node(sourceNode->data.id,sourceNode->data.year,sourceNode->data.month,sourceNode->data.temperature);
			sourceNode = sourceNode->next;
			prev = prev->next;
		}
		tail = prev;
		tail->next = nullptr;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& source) 
{
	// Implement this function
	LinkedList* newList = new LinkedList();
	if(source.head != nullptr)
	{
		Node* sourceNode = source.head;
		newList->head->data = sourceNode->data;
		sourceNode = sourceNode->next;
		Node* prev = newList->head;
		while(sourceNode)
		{
			prev->next = new Node(sourceNode->data.id,sourceNode->data.year,sourceNode->data.month,sourceNode->data.temperature);
			sourceNode = sourceNode->next;
			prev = prev->next;
		}
		tail = prev;
		tail->next = nullptr;
	}
	return *newList;
}

void LinkedList::insert(string location, int year, int month, double temperature) 
{
	// Implement this function
	Node *n = new Node(location,year,month,temperature);
	if(head == nullptr)
	{
		head = n;
		head->next = nullptr;
		tail = head;
		return;
	}
	else if(head->next == nullptr)
	{
		if(n->data < head->data)
		{
			n->next = head;
			head = n;
			tail = head->next;
			tail->next = nullptr;
		}
		else
		{
			head->next = n;
			n->next = nullptr;
		}
	}
	else
	{
		Node* prev = head;
		Node* curr = head->next;
		while(curr)
		{
			if(n->data < curr->data)
				break;
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
		prev->next = n;
		n->next = curr;
	}
}

void LinkedList::clear() 
{
	// Implement this function
	Node* next = nullptr;
	while(head)
	{
		next = head->next;
		delete head;
		head = next;
	}
	head = nullptr;
	head->next = nullptr;
	tail = head;
}

Node* LinkedList::getHead() const 
{
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const 
{
	stringstream output;
	// Implement this function
	Node* n = head;
	while(n)
	{
		output << n->data.id << " " << n->data.year << " " << n->data.month << " " << n->data.temperature;
		output << endl;
		n = n->next;
	}
	return output.str();
}

double LinkedList::calculateAverage(string location, int year1, int year2)
{
	int count = 0;
	double total = 0.0;
	Node* n = head;
	while(n)
	{
		if(n->data.id == location)
		{
			if(n->data.year >= year1 && n->data.year <= year2)
			{
				total += n->data.temperature;
				count ++;
			}
		}
		n = n->next;
	}
	if(count == 0)
		return -99.99;
	else
		return (total/count);
}

int LinkedList::calculateMode(string location, int year1, int year2)
{
	vector<int> set(100,0);
	double temp;
	int roundTemp;
	bool inHere = false;
	Node* n = head;
	while(n != nullptr)
	{
		if(n->data.id == location)
		{
			if(n->data.year >= year1 && n->data.year <= year2)
			{
				inHere = true;
				temp = n->data.temperature;
				if(temp-trunc(temp) <= .5)
					roundTemp = trunc(temp);
				else
					roundTemp = trunc(temp)+1;
				roundTemp += 50;
				set.at(roundTemp) += 1;
			}
		}
		temp = 0;
		roundTemp = 0;
		n = n->next;
	}
	if(!inHere)
		return -99;
	else
	{	
		int mode = 0;
		int modeCount = set.at(mode);
		for(int i=0;i<set.size();++i)
		{
			if(set.at(i)>=modeCount)
			{
				mode = i;
				modeCount = set.at(mode);
			}
		}
		return (mode-50);
	}
}


ostream& operator<<(ostream& os, const LinkedList& ll) 
{
	/* Do not modify this function */
	os << ll.print();
	return os;
}
