#include "Customer.h"
using namespace std;

Customer::Customer(int customerID, string name1, bool credit1)
{
	if(name1 == "")
		throw runtime_error("The customer must have a name.");
	else
	{
		name = name1;
		id = customerID;
		credit = credit1;
		balance = 0;
	}
}

int const Customer::getID()
{
	return id;
}

string const Customer::getName()
{
	return name;
}

void Customer::setName(string name1)
{
	if(name1 == "")
		throw runtime_error("Customer must have a name");
	else
		name = name1;
}

bool const Customer::getCredit()
{
	return credit;
}

void Customer::setCredit(bool hasCredit)
{
	credit = hasCredit;
}

double const Customer::getBalance()
{
	return balance;
}

void Customer::processPayment(double amount)
{
	if(amount < 0)
		throw runtime_error("Amount can't be negative");
	else
		balance += amount;
}

void Customer::processPurchase(double amount, Product product)
{
	if(amount < 0)
		throw runtime_error("Amount can't be negative");
	else if(!credit && balance < amount)
		throw runtime_error("insuffiecient funds");
	else
	{
		balance -= amount;
		Product temp = Product(product.getID(),product.getName());
		productsPurchased.push_back(temp);
	}
}

string const Customer::getProductsPurchased()
{
	string temp = "";
	stringstream ss;
	for(int i=0;i<productsPurchased.size();++i)
	{
		ss << "Product Name: ";
		ss << productsPurchased.at(i).getName();
		ss << "\n";
		ss << "Product ID: ";
		ss << productsPurchased.at(i).getID();
		ss << "\n";
		ss << "\n";
	}
	return ss.str();
}

ostream& operator<<(ostream &os, Customer& c)
{
	string fix = "";
	if(c.getCredit() == 1)
		fix = "true";
	else
		fix = "false";
	
	os << "Customer Name: " << c.getName() << endl;
	os << "Customer ID: " << c.getID() << endl;
	os << "Has Credit: " << fix << endl;
	os << "Balance: " << c.getBalance() << endl;
	os << "Products Purchased --" << endl << endl;
	os << c.getProductsPurchased();
}