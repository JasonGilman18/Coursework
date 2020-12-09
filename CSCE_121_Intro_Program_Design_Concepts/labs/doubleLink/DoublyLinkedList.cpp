#include "DoublyLinkedList.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
	head = nullptr;
	tail = head;
}

DoublyLinkedList::DoublyLinkedList(int val)
{
	head = new Node(val);
	tail = head;
}

DoublyLinkedList::~DoublyLinkedList()
{
	while(head!=nullptr)
	{
		delete head;
		head = head->next;
	}
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList const& list)
{
	Node* curr = list.head;
	head = new Node();
	head->data = curr->data;
	Node* previ = head;
	curr = curr->next;
	while(curr!=nullptr)
	{
		Node* newNode = new Node();
		newNode->data = curr->data;
		newNode->prev = previ;
		previ->next = newNode;
		curr = curr->next;
		previ = previ->next;
	}
	tail = previ;
	tail->next = nullptr;
}

DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList const& list)
{
	while(head!=nullptr)
	{
		delete head;
		head = head->next;
	}
	Node* curr = list.head;
	head = new Node();
	head->data = curr->data;
	Node* previ = head;
	curr = curr->next;
	while(curr!=nullptr)
	{
		Node* newNode = new Node();
		newNode->data = curr->data;
		newNode->prev = previ;
		previ->next = newNode;
		curr = curr->next;
		previ = previ->next;
	}
	tail = previ;
	tail->next = nullptr;
}

bool operator==(DoublyLinkedList const& list1, DoublyLinkedList const& list2)
{
	Node* head1 = new Node();
	Node* head2 = new Node();
	head1->data = list1.get_head().data;
	head1->next = list1.get_head().next;
	head2->data = list2.get_head().data;
	head2->next = list2.get_head().next;
	bool equal = true;
	while(head1 != nullptr && head2 != nullptr)
	{
		if(head1->data != head2->data)
		{
			equal = false;
			break;
		}
		if(head1->next != nullptr && head2->next != nullptr)
		{
			head1 = head1->next;
			head2 = head2->next;
		}
		else
			break;
	}
	return equal;
}

DoublyLinkedList& DoublyLinkedList::operator+=(DoublyLinkedList const& list)
{
	Node* curr = list.head;
	Node* lhs = head;
	head = new Node();
	head->data = lhs->data + curr->data;
	Node* previ = head;
	curr = curr->next;
	lhs = lhs->next;
	while(curr!=nullptr && lhs!=nullptr)
	{
		Node* newNode = new Node();
		newNode->data = lhs->data + curr->data;
		newNode->prev = previ;
		previ->next = newNode;
		curr = curr->next;
		lhs = lhs->next;
		previ = previ->next;
	}
	tail = previ;
	tail->next = nullptr;
}

void DoublyLinkedList::insert_back(int val)
{
	Node* temp = new Node(val);
	if(head == nullptr)
	{
		head = temp;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
	}
	else if(head == tail)
	{
		tail = temp;
		tail->prev = head;
		head->next = tail;
	}
	else
	{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		tail->next = nullptr;
	}
}

void DoublyLinkedList::insert_front(int val)
{
    Node* temp = new Node(val);
    if(head==nullptr)
	{
		head = temp;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
	}
	else if(head == tail)
	{
		head = temp;
		head->next = tail;
		tail->prev = head;
	}
	else
	{
		head->prev = temp;
		temp->next = head;
		head = temp;
		head->prev = nullptr;
	}
}

void DoublyLinkedList::insert_at(int val, int idx)
{
	Node* temp = new Node(val);
	if(idx<0)
		throw "error";
	else if(head==nullptr)
	{
		head = temp;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
	}
	else if(idx == 0)
	{
		head->prev = temp;
		temp->next = head;
		head = temp;
		head->prev = nullptr;
	}
	else
	{
		Node* point = head;
		bool last = false;
		for(int i=0;i<idx;++i)
		{
			if(point->next != nullptr)
				point = point->next;
			else if(point->next == nullptr && idx-i > 1)
			{
				throw "error";
			}
			else
			{
				last = true;
				break;
			}
		}
		if(last)
		{
			temp->prev = point;
			point->next = temp;
			temp->next = nullptr;
			tail = temp;
		}
		else
		{
			temp->next = point;
			point->prev->next = temp;
			temp->prev = point->prev;
			point->prev = temp;
		}
	}
}

Node& DoublyLinkedList::find(int val)
{
	Node* loop = head;
	while(loop->next != nullptr)
	{
		if(loop->data == val)
			return **&loop;
		else
			loop = loop->next;
	}
	if(loop->data == val)
		return **&loop;
}

void DoublyLinkedList::delete_at(int idx)
{
	if(idx<0)
		throw "error";
	else if(head==nullptr)
	{
		throw "error";
	}
	else if(idx == 0)
	{
		head = head->next;
		head->prev = nullptr;
	}
	else
	{
		Node* point = head;
		bool last = false;
		for(int i=0;i<idx;++i)
		{
			if(point->next != nullptr)
				point = point->next;
			else if(point->next == nullptr && idx-i > 1)
			{
				throw "error";
			}
			else
			{
				last = true;
				break;
			}
		}
		if(last)
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		else
		{
			point->prev->next = point->next;
			point->next->prev = point->prev;
		}
	}
}

Node& DoublyLinkedList::get_head()
{
    return *head;
}

Node& DoublyLinkedList::get_tail()
{
    return *tail;
}

Node const& DoublyLinkedList::get_head() const
{
    return *head;
}

Node const& DoublyLinkedList::get_tail() const
{
    return *tail;
}

ostream& operator<<(ostream &os, DoublyLinkedList const& ll) {
    os << "Doubly Linked List" << endl;
    if (&(ll.get_head()) == nullptr)
        return (os << "Empty" << endl);
    os << "Head: " << &(ll.get_head()) << "\t Tail: " << &(ll.get_tail()) << endl;
    Node const* curr = &(ll.get_head());
    os << "Nodes (accessible from head to tail):" << endl << endl;
    os << setw(16) << setfill(' ') << ' ' << ' ' << center("prev", 15) << ' ' << center("data", 15) << ' ' << center("next", 15) << endl;
    while (curr != nullptr) {
        ostringstream oss; oss << (curr->prev); string prev = oss.str(); oss.str(""); oss << (curr->next); string next = oss.str(); oss.str(""); oss << (curr->data); string data = oss.str(); oss.str(""); oss << curr; string address = oss.str();
        os << setw(16) << setfill(' ') << ' ' << '.' << setw(16) << setfill('-') << '.' << setw(16) << '.' << setw(16) << '.' << endl;
        os << setw(16) << setfill(' ') << center(address,15) << '|' << setw(15) << setfill(' ') << center(prev, 15) << '|' << setw(15) << center(data, 15) << '|' << setw(15) << center(next, 15) << '|'<< endl;
        os << setw(16) << setfill(' ') << ' ' << '\'' << setw(16) << setfill('-') << '\'' << setw(16) << '\'' << setw(16) << '\'' << endl;
        os << endl;
        curr = curr->next;
    }
    return os;
}

string center (const string &str, const int col_width)
{
    // quick and easy (but error-prone) implementation
    int padl = (col_width - str.length()) / 2;
    int padr = (col_width - str.length()) - padl;
    string strf = string(padl, ' ') + str + string(padr, ' ');
    return strf;
}