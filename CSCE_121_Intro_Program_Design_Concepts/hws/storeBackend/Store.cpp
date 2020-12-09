#include "Store.h"
using namespace std;

Store::Store()
{
	name = "";
}

Store::Store(string name1)
{
	name = name1;
}

string Store::getName()
{
	return name;
}

void Store::setName(string name1)
{
	name = name1;
}

void Store::addProduct(int productID, string productName)
{
	bool match = false;
	for(int i=0;i<products.size();++i)
	{
		if(products.at(i).getID() == productID)
		{
			throw runtime_error("ID belongs to another product");
			match = true;
		}
	}
	if(!match)
	{
		Product temp = Product(productID,productName);
		products.push_back(temp);
	}
}

Product& Store::getProduct(int productID)
{
	for(int i=0;i<products.size();++i)
	{
		if(products.at(i).getID() == productID)
			return products.at(i);
	}
	throw runtime_error("ID does not match any products");
}

void Store::addCustomer(int customerID, string customerName, bool credit1)
{
	bool match = false;
	for(int i=0;i<customers.size();++i)
	{
		if(customers.at(i).getID() == customerID)
		{
			throw runtime_error("ID belongs to another customer");
			match = true;
		}
	}
	if(!match)
	{
		Customer temp = Customer(customerID,customerName,credit1);
		customers.push_back(temp);
	}
}

Customer& Store::getCustomer(int customerID)
{
	for(int i=0;i<customers.size();++i)
	{
		if(customers.at(i).getID() == customerID)
			return customers.at(i);
	}
	throw runtime_error("ID does not match any customers");
}

void Store::takeShipment(int productID, int quantity, double cost)
{
	bool found = false;
	for(int i=0;i<products.size();++i)
	{
		if(products.at(i).getID() == productID)
		{
			products.at(i).addShipment(quantity,cost);
			found = true;
		}
	}
	if(!found)
		throw runtime_error("Product ID does not match any products");
}

void Store::takePayment(int customerID, double amount)
{
	bool found = false;
	for(int i=0;i<customers.size();++i)
	{
		if(customers.at(i).getID() == customerID)
		{
			customers.at(i).processPayment(amount);
			found = true;
		}
	}
	if(!found)
		throw runtime_error("Customer ID does not match any customers");
}

void Store::sellProduct(int customerID, int productID, int quantity)
{
	/*
	try
	{
		bool made = false;
		Product temp(productID,"temp");
		for(int i=0;i<products.size();++i)
		{
			if(products.at(i).getID() == productID)
			{
				temp = products.at(i);
				made = true;
			}
		}
		if(!made)
			throw runtime_error("Product id does not match any products.");
		else
		{
			temp.reduceInventory(quantity);
			Customer cust(customerID,"temp");
			made = false;
			for(int i=0;i<customers.size();++i)
			{
				if(customers.at(i).getID() == customerID)
				{
					cust = customers.at(i);
					made = true;
				}
			}
			if(!made)
				throw runtime_error("Customer id does not match and customers");
			else
			{
				cust.processPayment(temp.getPrice()*quantity);
				cust.processPurchase(temp.getPrice()*quantity,temp);
			}
		}
	}
	catch(runtime_error e)
	{
		cout << e.what() << endl;
	}
	*/
	
	Product temp(productID,"temp");
	Customer cust(customerID,"temp");
	bool made = false;
	
	for(int i=0;i<products.size();++i)
	{
		if(products.at(i).getID() == productID)
		{
			temp = products.at(i);
			made = true;
		}
	}
	if(!made)
		throw runtime_error("Product id does not match any products.");
	made = false;
	for(int i=0;i<customers.size();++i)
	{
		if(customers.at(i).getID() == customerID)
		{
			cust = customers.at(i);
			made = true;
		}
	}
	if(!made)
		throw runtime_error("Customer id does not match and customers");
	
	if(!(temp.getInventoryCount() - quantity < 0))
	{
		temp.reduceInventory(quantity);	
		cust.processPurchase(temp.getPrice()*quantity,temp);
	}
	else
		throw runtime_error("not enough inventory");
}

string Store::listProducts()
{
	string temp = "";
	for(int i=0;i<products.size();++i)
	{
		cout << products.at(i);
	}
	return temp;
}

string Store::listCustomers()
{
	string temp = "";
	for(int i=0;i<customers.size();++i)
	{
		cout << customers.at(i);
	}
	return temp;
}