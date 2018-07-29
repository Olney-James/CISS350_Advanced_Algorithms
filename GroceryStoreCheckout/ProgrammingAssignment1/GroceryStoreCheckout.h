#ifndef GROCERYSTORECHECKOUT_H
#define GROCERYSTORECHECKOUT_H
#pragma once
#include <string>

using namespace std;

struct product;

class GroceryStoreCheckout {
private:
	struct product {
	private:
		int productNumber;
		string description;
		double price;
		char tax;
	public:
		product();
		product(int pN, string d, double p, char t);
	};
public:

};


#endif // !GROCERYSTORECHECKOUT_H