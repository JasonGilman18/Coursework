#include "Product.h"
using namespace std;

Product::Product(int productID, string productName)
{
	if(productName == "")
		throw runtime_error("Product must have a name");
	else
	{
		id = productID;
		name = productName;
		inventory = 0;
		numSold = 0;
		description = "";
		totalPaid = 0.0;
	}
}

int const Product::getID()
{
	return id;
}

string const Product::getName()
{
	return name;
}

void Product::setName(string productName)
{
	if(productName == "")
		throw runtime_error("Product must have a name");
	else
		name = productName;
}

string const Product::getDescription()
{
	return description;
}

void Product::setDescription(string description1)
{
	description = description1;
}

int const Product::getNumberSold()
{
	return numSold;
}

double const Product::getTotalPaid()
{
	return totalPaid;
}

int const Product::getInventoryCount()
{
	return inventory;
}

void Product::addShipment(int shipmentQuantity, double shipmentCost)
{
	if(shipmentCost < 0)
		throw runtime_error("The shipment cost can't be negative");
	else if(shipmentQuantity < 0)
		throw runtime_error("The shipment quantity can't be negative");
	else
	{
		inventory += shipmentQuantity;
		totalPaid += shipmentCost;
	}
}

void Product::reduceInventory(int purchaseQuantity)
{
	if(purchaseQuantity < 0)
		throw runtime_error("Purchase quantity can't be negative");
	else if(inventory-purchaseQuantity < 0)
		throw runtime_error("Not enough inventory");
	else
	{
		inventory -= purchaseQuantity;
		numSold += purchaseQuantity;
	}
}

double const Product::getPrice()
{
	if(totalPaid <= 0 || inventory <= 0)
		throw runtime_error("Cannot calculate price");
	else
		return (totalPaid/((double)(inventory+numSold)))*1.25;
}

ostream& operator<<(ostream &os, Product& p)
{
	os << "Product Name: " << p.getName() << endl;
	os << "Product ID: " << p.getID() << endl;
	os << "Description: " << p.getDescription() << endl;
	os << "Inventory: " << p.getInventoryCount() << endl;
	os << "Number Sold: " << p.getNumberSold() << endl;
	os << "Total Paid: " << p.getTotalPaid() << endl;
	os << "Price: " << p.getPrice() << endl;
}