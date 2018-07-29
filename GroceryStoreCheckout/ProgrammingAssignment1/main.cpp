/***********************************************************
Program: "main.cpp" (Week 1 Programming Assignment 1)

This program simulates the operation of a grocery store checkout system. Your program should first 
build a data structure to contain information on all the products available in the store. Then the 
program should print the cash register receipt for each customer.

Author: James Olney
Created: 07/01/2017
Revisions:N/A
*******************/

#include <fstream>
#include <ctime>
#include "Product.h"

product & readInventoryInfoFromFileToArray(ifstream &infile, product *array) {
	string input;
	product myProduct;
	int x = 0;
	int index = 0;
	if (infile) {
		while (infile >> input) {
			switch (x) {
				case 0: myProduct.setProductNumber(stoi(input));
					break;
				case 1: myProduct.setDescription(input);
					break;
				case 2: myProduct.setPrice(stod(input));
					break;
				case 3: myProduct.setTax(input[0]);
					break;
			}
			x++;
			if (x > 3) {
				x = 0;
				array[index] = myProduct;
				cout << array[index];
				index++;
			}
		}
		infile.close();
	}
	else {
		cout << "ERROR: Cannot open file.\n";
	}
	return *array;
}

void echoPrintInventoryToOutputFile(ofstream &outfile, product *array, const int size) {
	for (int x = 0; x < size; x++) {
		if (array[x].getProductNumber() == 0) {
			break;
		}
		outfile << array[x];
	}
}
 
bool productHasNotAlreadyBeenOrdered(ofstream &outfile, int productNumber, product *array, int arraySize) { //Handle Duplicate product numbers
	bool beenOrdered = false;
	for (int x = 0; x < arraySize; x++) {
		if (array[x].getProductNumber() == productNumber) {
			beenOrdered = true;
			cout << "***" << productNumber << " has already been ordered***" << endl;			// write an error message to the console 
			outfile << "***" << productNumber << " has already been ordered***" << endl;	// write an error message to the output file
			break;																			// skip the second entry.
		}
	}
	return beenOrdered;
}

product findProduct(ofstream &outfile, int productNumber, product *array, int arraySize) {
	for (int x = 0; x < arraySize; x++) {
		if (array[x].getProductNumber() == 0) {											//Handle missing product number by writing an error message on the receipt. 
			cout << "*** item " << to_string(productNumber) << " not in inventory ***" << endl;
			outfile << "*** item " << to_string(productNumber) << " not in inventory ***" << endl;
			return product();															//Then ignore that product number and continue with the next item
		}
		else if (array[x].getProductNumber() == productNumber) {
			return array[x];
		}
		
	}
}

int main() {
	int exit;
	int productNumber = 1;
	int times = 0;
	int quantity;
	int customer = 1;
	char proceed = 'Y';
	const int ARRAYSIZE = 50;															//assume max num of products is 50	
	product arrayOfProductNumbers[ARRAYSIZE];											//Inventory info stored in an array of product records
	product arrayOfOrderedProducts[ARRAYSIZE];											//products ordered
	int quantityOrdered[ARRAYSIZE];														//parallel to arrayOfOrderedProducts to match quantity to product ordered
	ifstream inventory;
	string inventoryFileName = "Invent.txt";
	inventory.open(inventoryFileName, ios::in);
	ofstream receipt;
	string receiptFileName = "Receipt.txt";

	readInventoryInfoFromFileToArray(inventory, arrayOfProductNumbers);					//read in all inventory info from "Invent.txt" 
	
	receipt.open(receiptFileName);
	echoPrintInventoryToOutputFile(receipt, arrayOfProductNumbers, ARRAYSIZE);			//inventory is echo printed to the output file
	//UPDATE:: print date and time at top of receipt OPTIONAL
	
	while (proceed = 'Y') {
		cout << "CUSTOMER " << customer << endl;
		receipt << "CUSTOMER " << customer << endl;
		cout << "Please input product# and qty(enter '0 0' to end order): " << endl;	//prompt cashier to input the order
		while (productNumber > 0) {
			cin >> productNumber >> quantity;
			if (quantity > 0 && quantity <= 100) {
				if (productNumber != 0 && !productHasNotAlreadyBeenOrdered(receipt, productNumber, arrayOfOrderedProducts, ARRAYSIZE)) {
					product temp = findProduct(receipt, productNumber, arrayOfProductNumbers, ARRAYSIZE);
					if (!temp.getProductNumber() == 0) {
						arrayOfOrderedProducts[times] = temp;
						quantityOrdered[times] = quantity;
						receipt << arrayOfOrderedProducts[times].getDescription() << " " << quantityOrdered[times] << " @ " << to_string(arrayOfOrderedProducts[times].getPrice()) << " " << to_string(arrayOfOrderedProducts[times].getPrice() * quantityOrdered[times]) << endl;
					}																	//above: The receipts should be nicely formatted, with the product description (not the product number), number of items, item price, and total price for each product printed on a single line.
				}
			}
			if (productNumber != 0 && quantity < 1) {									//Handle Times not being in the range of 1-100
				cout << "***cannot order " << quantity << " of an item***" << endl;
				receipt << "***cannot order " << quantity << " of an item***" << endl;	//write an error to the output file
			}
			if (productNumber != 0 && quantity > 100) {
				cout << "***cannot order more than 100 of an item***" << endl;			//write an error to the console
				receipt << "***cannot order more than 100 of an item***" << endl;		//write an error to the output file
			}
			if (productNumber == 0) {													//a zero input for <product number> indicates the end of the customer's order.
				double subtotal = 0;													//At the end of each customer's order, the subtotal for all items, amount of tax on taxable items, and total bill should be printed, clearly labeled.
				for (int x = 0; x < ARRAYSIZE; x++) {
					subtotal += arrayOfOrderedProducts[x].getPrice() * quantityOrdered[x];
				}
				double tax = 0.27;														//(The tax rate is 7.5% for taxable items.)
				double total = subtotal + (subtotal * tax);
				receipt << "\t \t Subtotal " << subtotal << endl;
				receipt << "\t \t Tax      " << tax << endl;
				receipt << endl << "\t Total " << total << endl;
				break;
			}
		}
		cout << "Another Customer? (Y or N) :";											//ask the cashier if another customer is to be processed.
		cin >> proceed;																	//if 'Y', set up to process the next customer
		if (proceed == 'N') {															//if 'N', the program terminates with a friendly message
			break;
		}
		productNumber = 1;
		for (int x = 0; x < ARRAYSIZE; x++) {
			arrayOfOrderedProducts[x].emptyProduct();
		}
		cout << endl << endl;
		receipt << endl << endl;
		customer++;
	}
	cout << "enter 0 to exit...";
	cin >> exit;
}


