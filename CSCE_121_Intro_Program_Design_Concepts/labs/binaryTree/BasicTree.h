#ifndef BASICTREE_H
#define BASICTREE_H
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>

class BasicTree {
public:
    BasicTree();
    BasicTree(int);
	~BasicTree(); 
	BasicTree(BasicTree const& t);
    BasicTree& operator=(BasicTree const&);
    void insert(int);
    int const& find(int);

    // Traversals : Wrappers
    std::ostream& in_order(std::ostream& os = std::cout) {return in_order(root, os) << std::endl;}
    std::ostream& post_order(std::ostream& os = std::cout) {return post_order(root, os) << std::endl;}
    std::ostream& pre_order(std::ostream& os = std::cout) {return pre_order(root, os) << std::endl;}

    // operator<< support
    std::string to_str() const {std::stringstream ss; return (to_sstream(root, 0, "", ss)).str();}
private:
    Node* root;

    // Traversals : Actual
    std::ostream& in_order(Node*, std::ostream&);
    std::ostream& post_order(Node*, std::ostream&);
    std::ostream& pre_order(Node*, std::ostream&);

    // operator<< support
    std::stringstream& to_sstream(Node*, int, std::string, std::stringstream&) const;
};

std::ostream& operator<<(std::ostream&, BasicTree const&);
void destructorHelper(Node* n);
void copyHelper(Node* n);

#endif