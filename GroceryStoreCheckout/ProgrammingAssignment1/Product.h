/***********************************************************
Program: "Product.h" (Week 1 Programming Assignment 1)

This is the header file for Product.cpp.

Author: James Olney
Created: 07/01/2017
Revisions:N/A
*******************/
#ifndef PRODUCT_H
#define PRODUCT_H
#pragma once

#include <string>
#include <iostream>
using namespace std;

class product {
	private:
		int productNumber;
		string description;
		double price;
		char tax;
	public:
		product();
		product(int pN, string d, double p, char t);
		void setProductNumber(int pN);
		void setDescription(string d);
		void setPrice(double p);
		void setTax(char t);
		int getProductNumber();
		string getDescription();
		double getPrice();
		char getTax();
		friend ostream &operator << (ostream &, product &);
		void emptyProduct();
};

#endif