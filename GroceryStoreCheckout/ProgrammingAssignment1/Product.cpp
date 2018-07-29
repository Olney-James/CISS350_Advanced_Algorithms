/***********************************************************
Program: "Product.cpp" (Week 1 Programming Assignment 1)

This program creates the object for products used in main.cpp. where <product number> is a five-digit positive (nonzero) integer, <description> is a string of at most 
12 characters with no embedded blanks, <price> is a real number, and <tax> is a character ('T' if the product is taxable; 'N' if it is not taxable). The ostream operator 
is overloaded, and the function emptyProduct helps clear an array of Products if needed.

Detail: Product

Author: James Olney
Created: 07/01/2017
Revisions:N/A
*******************/
#include "Product.h"

product::product()
{
	productNumber = 0;
	description = "";
	price = 0.0;
	tax = 'T';

}

product::product(int pN, string d, double p, char t)
{
	productNumber = pN;
	description = d;
	price = p;
	tax = t;
}

void product::setProductNumber(int pN)
{
	productNumber = pN;
}

void product::setDescription(string d)
{
	description = d;
}

void product::setPrice(double p)
{
	price = p;
}

void product::setTax(char t)
{
	tax = t;
}

int product::getProductNumber()
{
	return productNumber;
}

string product::getDescription()
{
	return description;
}

double product::getPrice()
{
	return price;
}

char product::getTax()
{
	return tax;
}

void product::emptyProduct()
{
	productNumber = 0;
	description = "";
	price = 0.0;
	tax = ' ';
}

ostream & operator<<(ostream &strm, product &obj)
{
	strm << to_string(obj.getProductNumber()) << " " << obj.getDescription() << " " << to_string(obj.getPrice()) << " " << to_string(obj.getTax()) << endl;
	return strm;
}