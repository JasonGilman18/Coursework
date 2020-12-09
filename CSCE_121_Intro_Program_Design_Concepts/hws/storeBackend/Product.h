#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

class Product
{
	public:
		Product(int productID, std::string productName);
		int const getID();
		std::string const getName();
		void setName(std::string productName);
		std::string const getDescription();
		void setDescription(std::string description1);
		int const getNumberSold();
		double const getTotalPaid();
		int const getInventoryCount();
		void addShipment(int shipmentQuantity, double shipmentCost);
		void reduceInventory(int purchaseQuantity);
		double const getPrice();

	private:
		int id;
		int inventory;
		int numSold;
		std::string name;
		std::string description;
		double totalPaid;
};

std::ostream& operator<<(std::ostream &os, Product& p);

#endif