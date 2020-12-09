#ifndef STORE_H
#define STORE_H
#include "Product.h"
#include "Customer.h"
#include <string>
#include <vector>
#include <iostream>

class Store
{
	public:
		Store();
		Store(std::string name1);
		std::string getName();
		void setName(std::string name1);
		void addProduct(int productID, std::string productName);
		Product& getProduct(int productID);
		void addCustomer(int customerID, std::string customerName, bool credit1=false);
		Customer& getCustomer(int customerID);
		void takeShipment(int productID, int quantity, double cost);
		void takePayment(int customerID, double amount);
		void sellProduct(int customerID, int productID, int quantity);
		std::string listProducts();
		std::string listCustomers();
	
	private:
		std::string name;
		std::vector<Product> products;
		std::vector<Customer> customers;
};
#endif