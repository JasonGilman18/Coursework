#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node()// remember to initialize next to nullptr
{
	next = nullptr;
	data = TemperatureData();
}

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature) // remember to initialize next to nullptr
{
	next = nullptr;
	data = TemperatureData(id,year,month,temperature);
}

bool Node::operator<(const Node& b) 
{
	return this->data < b.data;
}
