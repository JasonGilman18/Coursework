#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Product.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <ostream>

class Customer
{
	public:
		Customer(int customerID, std::string name, bool credit1=false);
		int const getID();
		std::string const getName();
		void setName(std::string name1);
		bool const getCredit();
		void setCredit(bool hasCredit);
		double const getBalance();
		void processPayment(double amount);
		void processPurchase(double amount, Product product);
		std::string const getProductsPurchased();
		
	private:
		int id;
		std::string name;
		bool credit;
		double balance;
		std::vector<Product> productsPurchased;
};

std::ostream& operator<<(std::ostream &os, Customer& c);

#endif