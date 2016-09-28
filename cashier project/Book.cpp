#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <string>
#include "Book.h"
using namespace std;

Book::Book()
{
	isbn = "";
	title = "";
	author = "";
	publisher = "";
	dateAdded = "";
	quantity = 0;
	wholeSalePrice = 0;
	retailPrice = 0;
}

void Book::setIsbn(string i)
{
	isbn = i;
}
void Book::setTitle(string t)
{
	title = t;
}
void Book::setAuthor(string a)
{
	author = a;
}
void Book::setPublisher(string p)
{
	publisher = p;
}
void Book::setDate(string d)
{
	dateAdded = d;
}
void Book::setQuantity(int q)
{
	quantity = q;
	if (quantity < 0)
		quantity = 0;
}
void Book::setWholeSalePrice(double pW)
{
	wholeSalePrice = pW;
	if (wholeSalePrice < 0)
		wholeSalePrice = 0;
}
void Book::setRetailPrice(double pR)
{
	retailPrice = pR;
	if (retailPrice < 0)
		retailPrice = 0;
}
string Book::getIsbn()
{
	return isbn;
}
string Book::getTitle()
{
	return title;
}
string Book::getAuthor()
{
	return author;
}
string Book::getPublisher()
{
	return publisher;
}
string Book::getDate()
{
	return dateAdded;
}
double Book::getWholeSalePrice()
{
	return wholeSalePrice;
}
double Book::getRetailPrice()
{
	return retailPrice;
}
int Book::getQuantity(){ return quantity; }
bool Book::badIsbn()
{
	bool isNumber = true;
	for (int i = 0; i < isbn.length(); i++)
		if (!isdigit(isbn.at(i)))
		{
			isNumber = false;
			break;
		}

	if ((isbn.length() != 10 && isbn.length() != 13) || !isNumber)
	{
		cout << "\nInvalid ISBN!";
		return true;
	}
	return
		false;
}
bool Book::badDate()
{

	string date, y, m, d;
	date = dateAdded;
	string message = "\nINVALID DATE!PLEASE USE mm/dd/yyyy FORMAT.\n";
	if (date.length() != 10)
	{
		cout << message;
		return true;
	}

	m.assign(date, 0, 2);
	d.assign(date, 3, 2);
	y.assign(date, 6, 4);
	if (atoi(y.c_str()) >= 2000 && atoi(y.c_str()) <= 2020)
		if (atoi(m.c_str()) == 4 || atoi(m.c_str()) == 6 || atoi(m.c_str()) == 9 || atoi(m.c_str()) == 11)
			if (atoi(d.c_str()) >= 1 && atoi(d.c_str()) <= 30)
				return false;
			else
			{
				cout << message;
				return true;
			}
		else if (atoi(m.c_str()) == 1 || atoi(m.c_str()) == 3 || atoi(m.c_str()) == 5 || atoi(m.c_str()) == 7 || atoi(m.c_str()) == 8 || atoi(m.c_str()) == 10 || atoi(m.c_str()) == 12)
			if (atoi(d.c_str()) >= 1 && atoi(d.c_str()) <= 31)
				return false;
			else
			{
				cout << message;
				return true;
			}
		else if (atoi(m.c_str()) == 2)
			if (atoi(d.c_str()) >= 1 && atoi(d.c_str()) <= 29)
				return false;
			else
			{
				cout << message;
				return true;
			}
		else
		{
			cout << message;
			return true;
		}
	else
	{
		cout << message;
		return true;
	}
}


int Book::operator > (Book &rightObj)
{
	string d1, d1y, d1m, d1d;
	string d2, d2y, d2m, d2d;
	d1 = dateAdded;//object is being passed by reference
	d2 = rightObj.getDate();
	//break down the dates into substring for comparison
	d1m.assign(d1, 0, 2);
	d1d.assign(d1, 3, 2);
	d1y.assign(d1, 6, 4);
	d2m.assign(d2, 0, 2);
	d2d.assign(d2, 3, 2);
	d2y.assign(d2, 6, 4);

	if (d1y != d2y)
	{
		if (d1y < d2y)
			return 1;
		else
			return -1;
	}
	else if (d1m != d2m)
	{
		if (d1m < d2m)
			return 1;
		else
			return -1;
	}
	else if (d1d != d2d)
	{
		if (d1d < d2d)
			return 1;
		else
			return -1;
	}
	else
		return 0;

}
ostream &operator << (ostream &strm, const Book &obj)//send book object to the screen
{

	strm << left << setw(14) << obj.isbn << setw(42) << obj.title << setw(20) << obj.author
		<< setw(27) << obj.publisher << setw(14) << obj.dateAdded
		<< "$" << setw(10) << obj.wholeSalePrice << "$" << setw(10)
		<< obj.retailPrice << setw(2) << obj.quantity << "\n";
	return strm;
}
istream &operator >> (istream &strm, Book &obj)//assign user entered values to book object
{
	cin.clear();
	cin.sync();
	cout << "\nEnter new book Info.\n";

	do{
		cout << "\nISBN: ";
		getline(strm, obj.isbn, '\n');
	} while (obj.badIsbn());

	cout << "Title: ";
	getline(strm, obj.title, '\n');
	cout << "Author: ";
	getline(strm, obj.author, '\n');
	cout << "Publisher: ";
	getline(strm, obj.publisher, '\n');
	do{
		cout << "Date Added[mm/dd/yyyy]: ";
		getline(strm, obj.dateAdded, '\n');
	} while (obj.badDate());
	cout << "Whole Sale Price: ";
	strm >> obj.wholeSalePrice;
	cout << "Retail Price: ";
	strm >> obj.retailPrice;
	cout << "Quantity: ";
	strm >> obj.quantity;

	return strm;
}

//read values from a book object and write it to a file 
fstream &operator << (fstream &strm, const Book &obj){
	strm << obj.isbn << ',' << obj.title << "," << obj.author << ","
		<< obj.publisher << "," << obj.dateAdded << "," << obj.wholeSalePrice
		<< ',' << obj.retailPrice << ',' << obj.quantity << ",";
	return strm;
}

//read values from a file and assign it to book object
fstream &operator >> (fstream &strm, Book &obj)
{
	string info;
	getline(strm, info, ',');
	if (info.length() >= 10)
	{
		obj.setIsbn(info);
		getline(strm, info, ',');
		obj.setTitle(info);
		getline(strm, info, ',');
		obj.setAuthor(info);
		getline(strm, info, ',');
		obj.setPublisher(info);
		getline(strm, info, ',');
		obj.setDate(info);
		getline(strm, info, ',');
		obj.setWholeSalePrice(atof(info.c_str()));
		getline(strm, info, ',');
		obj.setRetailPrice(atof(info.c_str()));
		getline(strm, info, ',');
		obj.setQuantity(atoi(info.c_str()));
	}
	return strm;
}


