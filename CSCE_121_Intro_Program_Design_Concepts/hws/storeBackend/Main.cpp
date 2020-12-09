#include "Store.h"
#include "Product.h"
#include "Customer.h"
using namespace std;

int main()
{/*
Store s;

ASSERT_EQ(s.getName(),"");

Store s2("Things to Buy");

ASSERT_EQ(s2.getName(),"Things to Buy");

// Testing addProduct and getProduct
s.addProduct(123,"towel");

s.getProduct(123).setDescription("For drying.");
ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),0);
ASSERT_EQ(s.getProduct(123).getTotalPaid(),0.0);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 0);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

s.addProduct(234,"mask");
s.getProduct(234).setDescription("For hiding.");
ASSERT_EQ(s.getProduct(234).getID(),234);
ASSERT_EQ(s.getProduct(234).getName(),"mask");
ASSERT_EQ(s.getProduct(234).getInventoryCount(),0);
ASSERT_EQ(s.getProduct(234).getTotalPaid(),0.0);
ASSERT_EQ(s.getProduct(234).getNumberSold(), 0);
ASSERT_EQ(s.getProduct(234).getDescription(),"For hiding.");

// adding product that is already there throws an exception
ASSERT_THROW(s.addProduct(123,"random"),std::runtime_error);

// check that getting product that is not there throws an exception
ASSERT_THROW(s.getProduct(555),std::runtime_error);

// check all is unchanged on product attempted to add again
ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),0);
ASSERT_EQ(s.getProduct(123).getTotalPaid(),0.0);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 0);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// Test addCustomer
s.addCustomer(987,"Joe Blockhead",true);

ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_EQ(s.getCustomer(987).getBalance(),0);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"");

// another customer with default false for credit
s.addCustomer(789, "Jane Grooves");
ASSERT_EQ(s.getCustomer(789).getID(),789);
ASSERT_EQ(s.getCustomer(789).getName(),"Jane Grooves");
ASSERT_EQ(s.getCustomer(789).getCredit(),false);
ASSERT_EQ(s.getCustomer(789).getBalance(),0);
ASSERT_EQ(s.getCustomer(789).getProductsPurchased(),"");

// adding customer that is already there throws an exception
ASSERT_THROW(s.addCustomer(987,"Someone new",false),std::runtime_error);

// check that getting customer that is not there throws an exception
ASSERT_THROW(s.getCustomer(555),std::runtime_error);

// check customer not changed that was attempted to add again
ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_EQ(s.getCustomer(987).getBalance(),0);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"");

// Test takeShipment
s.takeShipment(123,200,400);

ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),200);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 0);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// takeShipment throws exceptions for negative quantity or amount
ASSERT_THROW(s.takeShipment(123, -5, 100),std::runtime_error);
ASSERT_THROW(s.takeShipment(123, 5, -100),std::runtime_error);

// takeShipment throws exception for invalid product id
ASSERT_THROW(s.takeShipment(555,2,-2),std::runtime_error);

// check all is same after exceptions.
ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),200);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 0);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// test takePayment
s.takePayment(987,600);

ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_NEAR(s.getCustomer(987).getBalance(),600,.001);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"");

// takePayment throws exception for negative payment
ASSERT_THROW(s.takePayment(987,-50), std::runtime_error);

// takePayment throws exception for invalid customer id
ASSERT_THROW(s.takePayment(555,25),std::runtime_error);

// check all is same after exception
ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_NEAR(s.getCustomer(987).getBalance(),600,.001);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"");

// test sellProduct
s.sellProduct(987,123,10);

ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_NEAR(s.getCustomer(987).getBalance(),575,.001);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"Product Name: towel\nProduct ID: 123\n\n");

ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),190);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 10);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// check various parts of bad input for sellProduct
// bad amount
ASSERT_THROW(s.sellProduct(123,789,-10),std::runtime_error);

// check things remain unchanged
ASSERT_EQ(s.getCustomer(789).getID(),789);
ASSERT_EQ(s.getCustomer(789).getName(),"Jane Grooves");
ASSERT_EQ(s.getCustomer(789).getCredit(),false);
ASSERT_EQ(s.getCustomer(789).getBalance(),0);
ASSERT_EQ(s.getCustomer(789).getProductsPurchased(),"");

ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),190);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 10);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// sellProduct not enough balance
ASSERT_THROW(s.sellProduct(123,789,10),std::runtime_error);

// check things remain unchanged
ASSERT_EQ(s.getCustomer(789).getID(),789);
ASSERT_EQ(s.getCustomer(789).getName(),"Jane Grooves");
ASSERT_EQ(s.getCustomer(789).getCredit(),false);
ASSERT_EQ(s.getCustomer(789).getBalance(),0);
ASSERT_EQ(s.getCustomer(789).getProductsPurchased(),"");

ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),190);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 10);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");

// check sellProduct not enough inventory
ASSERT_THROW(s.sellProduct(123,987,200),std::runtime_error);

ASSERT_EQ(s.getCustomer(987).getID(),987);
ASSERT_EQ(s.getCustomer(987).getName(),"Joe Blockhead");
ASSERT_EQ(s.getCustomer(987).getCredit(),true);
ASSERT_NEAR(s.getCustomer(987).getBalance(),575,.001);
ASSERT_EQ(s.getCustomer(987).getProductsPurchased(),"Product Name: towel\nProduct ID: 123\n\n");

ASSERT_EQ(s.getProduct(123).getID(),123);
ASSERT_EQ(s.getProduct(123).getName(),"towel");
ASSERT_EQ(s.getProduct(123).getInventoryCount(),190);
ASSERT_NEAR(s.getProduct(123).getTotalPaid(),400,0.001);
ASSERT_EQ(s.getProduct(123).getNumberSold(), 10);
ASSERT_EQ(s.getProduct(123).getDescription(),"For drying.");
*/
}