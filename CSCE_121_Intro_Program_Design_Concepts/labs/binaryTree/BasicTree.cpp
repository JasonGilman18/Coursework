#include "BasicTree.h"
#include <queue>
#include <cstdio>
using namespace std;

class val_not_found{};

BasicTree::BasicTree() : root{nullptr} {}
BasicTree::BasicTree(int i) : root{new Node(i)} {}

BasicTree::BasicTree(BasicTree const& t)
{
	if(t.root != nullptr)
	{
		root = new Node();
		root->left = t.root->left;
		root->right = t.root->right;
		root->data = t.root->data;
		copyHelper(t.root->left);
		copyHelper(t.root->right);
	}
}

void copyHelper(Node* n)
{
	if(n == nullptr)
		return;
	else if(n != nullptr)
	{
		Node* temp = new Node();
		temp->left = n->left;
		temp->right = n->right;
		temp->data = n->data;
		copyHelper(n->left);
		copyHelper(n->right);
	}
}

BasicTree::~BasicTree()
{
	destructorHelper(root);
}

void destructorHelper(Node* n)
{
	if(n == nullptr)
		return;
	else if(n != nullptr)
	{
		destructorHelper(n->left);
		destructorHelper(n->right);
		delete n;
	}
}

BasicTree& BasicTree::operator=(BasicTree const& t)
{
	destructorHelper(root);
	if(t.root != nullptr)
	{
		root = new Node();
		root->left = t.root->left;
		root->right = t.root->right;
		root->data = t.root->data;
		copyHelper(t.root->left);
		copyHelper(t.root->right);
	}
}

void BasicTree::insert(int val)
{
    // 1. Check whether the tree is empty or not;
	if(root == nullptr)
		root = new Node(val);
	else
	{
		Node *curr = root;
		Node *parent = nullptr;
		while(curr != nullptr)
		{
			parent = curr;
			if(curr->data > val)
				curr = curr->left;
			else
				curr = curr->right;
		}
		if(parent->data > val)
		{
			parent->left = new Node(val);
			curr = parent->left;
			curr->parent = parent;
		}
		else
		{
			parent->right = new Node(val);
			curr = parent->right;
			curr->parent = parent;
		}
	}
    // 2a. if the tree is empty set root equal to a new node with the passed value and return.
    // 2b. Otherwise, find the proper location to tag on a new node storing the passed value on to the tree; be sure to set this node's Node* parent to the node preceding it in the tree.
}

ostream& BasicTree::in_order(Node *n, ostream &os)
{
    // 1. Traverse the left subtree by visiting node to the left of the current node.

    // 2. Visit the current node; insert its value to the stream.

    // 3. Traverse the right subtree by visiting node to the right of the current node.

    // 4. Return the stream
	
	if(n != nullptr)
	{
		in_order(n->left,os);
		os << n->data << " ";
		in_order(n->right,os);
	}
	else
		return os;
}

ostream& BasicTree::post_order(Node *n, ostream &os)
{
    // 1. Traverse the left subtree by visiting node to the left of the current node.

    // 2. Traverse the right subtree by visiting the node to the right of the current node.

    // 3. Visit the current node; insert its value to the stream.

    // 4. Return the stream
	
	if(n != nullptr)
	{
		post_order(n->left,os);
		post_order(n->right,os);
		os << n->data << " ";
	}
	else
		return os;
}

ostream& BasicTree::pre_order(Node *n, ostream &os)
{
    // 1. Visit the current node; insert its value to the stream.

    // 2. Traverse the left subtree by visiting node to the left of the current node.

    // 3. Traverse the right subtree by visiting the node to the right of the current node.

    // 4. Return the stream
	
	if(n != nullptr)
	{
		os << n->data << " ";
		pre_order(n->left,os);
		pre_order(n->right,os);
	}
	else
		return os;
}

int const& BasicTree::find(int val) {
    // 1. Search the tree for node containing val ...

    // 2a. If such node is found, return a constant reference to the int object contained in that node (to do this, simply return curr->val);

    // 2b. Otherwise, if such a node is not found, throw val_not_found{};
	
	if(root == nullptr)
		throw val_not_found{};
	else
	{
		Node *curr = root;
		while(curr != nullptr)
		{
			if(curr->data == val)
				return curr->data;
			else
			{
				if(curr->data > val)
					curr = curr->left;
				else
					curr = curr->right;
			}
		}
		throw val_not_found{};
	}
}

///////////////////////////////////////////////////////////////////////////////
// operator<< support
///////////////////////////////////////////////////////////////////////////////
stringstream& BasicTree::to_sstream(Node *n, int depth, string s, stringstream& os) const
{
    if (n==nullptr) {
        os << "Empty" << endl;
        return os;
    }
    os << "("<<n->data<<") Address: " << n << " Parent: " << n->parent << "\n";
    os << s << " `--[L]";
    s += " |  ";
    if (n->left)
        to_sstream(n->left, depth + 1, s, os);
    else
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());

    os << s << " `--[R]";
    s += "    ";
    if (n->right)
        to_sstream(n->right, depth + 1, s, os);
    else
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());
    return os;
}

ostream& operator<<(ostream& os, BasicTree const& bt)
{
    os << bt.to_str();
    return os;
}