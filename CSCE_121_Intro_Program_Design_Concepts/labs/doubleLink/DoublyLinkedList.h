#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include <string>
#include "Node.h"

class DoublyLinkedList {
public:
    DoublyLinkedList();
    DoublyLinkedList(int);
    ~DoublyLinkedList();
	DoublyLinkedList(DoublyLinkedList const&);
	DoublyLinkedList& operator=(DoublyLinkedList const&);
	DoublyLinkedList& operator+=(DoublyLinkedList const&);
    void insert_back(int);
    void insert_front(int);
    void insert_at(int, int);
    Node& find(int);
    void delete_at(int);
    Node& get_head();
    Node& get_tail();
    Node const& get_head() const;
    Node const& get_tail() const;
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    
};

std::string center (const std::string &str, const int col_width);
std::ostream& operator<<(std::ostream &os, DoublyLinkedList const& ll);
bool operator==(DoublyLinkedList const& list1, DoublyLinkedList const& list2);

#endif