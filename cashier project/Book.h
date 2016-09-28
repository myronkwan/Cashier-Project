
#define _CRT_SECURE_NO_WARNINGS
#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Book
{
	string isbn;
	string title;
	string author;
	string publisher;
	string dateAdded;
	int quantity;
	double wholeSalePrice;
	double retailPrice;

public:
	Book();
	void setIsbn(string);
	void setTitle(string);
	void setAuthor(string);
	void setPublisher(string);
	void setDate(string);
	void setQuantity(int);
	void setWholeSalePrice(double);
	void setRetailPrice(double);
	string getIsbn();
	string getTitle();
	string getAuthor();
	string getPublisher();
	string getDate();
	double getWholeSalePrice();
	double getRetailPrice();
	int getQuantity();
	bool badIsbn();
	bool badDate();

	friend ostream &operator << (ostream &strm, const Book &obj);
	friend istream &operator >> (istream &strm, Book &obj);
	friend fstream &operator << (fstream &strm, const Book &obj);
	friend fstream &operator >> (fstream &strm, Book &obj);
	int operator > (Book &rightObj);
	~Book(){}

};

#endif


