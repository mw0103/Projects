#include "BookRecord.h"
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Book_Database.h"
#pragma warning(disable : 4996)

using namespace std;

int main() {
	int test;
	
	BookRecord book1;
	BookRecord book2("Harry Potter", 6349, 418, 49.99);
	Book_Database inventory1;
	inventory1.readDatabase("BookData.txt");


	int numInStock;
	long stocknumber;
	double minPrice;
	double maxPrice;
	int s_classification;
	bool stop;
	int input;
	stop = false;
	
	
	inventory1.PrintAll();

	cout << "Enter the stock number in the inventory to delete: ";
	cin >> stocknumber;
	inventory1.removeBook(stocknumber);
	inventory1.PrintAll();

	cout << "Enter the stock number to search for: ";
	cin >> stocknumber;
	inventory1.searchByStockNumber(stocknumber);
	
	cout << "Enter minimum price to search for: ";
	cin >> minPrice;
	cout << "Enter the maximum price to search for: ";
	cin >> maxPrice;
	inventory1.searchByCost(minPrice, maxPrice);

	cout << "Enter a classification to search for: ";
	cin >> s_classification;
	inventory1.searchByClassification(s_classification);

	cout << "Enter a stock number to get the inventory for that item on file: " << endl;
	cin >> stocknumber;
	numInStock = inventory1.getNumInStock(stocknumber);
	cout << "Number in stock: " << numInStock << endl;
	
	while (!stop) {
		cout << "Would you like to create and add another book to the inventory? Press 1 to add 2 to exit" << endl;
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		char tempname[128];
		long tempsn;
		int tempcl;
		double tempcst;
		int tempcount;
		inventory1.PrintAll();
		cin.clear();
		if (input == 1) {
			BookRecord* temp = new BookRecord;
			
			cout << "Enter the name of the book: ";
			cin.getline(tempname, 128);
			//cin.ignore('\n');
			cout << "Enter the stock number: ";
			cin >> tempsn;
			//cin.ignore('\n');
			cout << "Enter the classification number: ";
			cin >> tempcl;
			//cin.ignore('\n');
			cout << "Enter the cost of the book: ";
			cin >> tempcst;
			//cin.ignore('\n');
			cout << "Enter the amount of this book to add: ";
			cin >> tempcount;

			temp->setName(tempname);
			temp->setStockNum(tempsn);
			temp->setClassification(tempcl);
			temp->setCost(tempcst);
			temp->setNumberInStock(tempcount);
			inventory1.addBook(temp);


		}
		else if (input == 2) {
			stop = true;
		}


		

	}

	
	return 0;
};