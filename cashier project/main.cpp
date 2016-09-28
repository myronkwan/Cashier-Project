#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include<limits>
#include "Book.h"

using namespace std;

void centerstring(char *s);
int checkBook(Book *b, string search);
int locateBook(Book *b, string isbn);
void writeBook(Book* b);
void displayBook(Book* b);
void wholesaleValue(Book* b);
void RetailValue(Book* b);
void addBook(Book* b);
void removeBook(Book* b);
void editBook(Book* b);
void quantityList(Book* b);
void inventoryList(Book* b);
void cashier(Book* b);
void ageSort(Book* b);
void priceList(Book* b);
void inventoryDatabaseModule(Book* b, char select2);
void reportModule(Book* b, char select3);
void transactionList();

void centerstring(char *s)
{
	cout << endl;
	int l = strlen(s);
	int pos = (int)((150 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";
	cout << s;
}
int locateBook(Book *b, string isbn)//return book position 
{
	for (int i = 0; i < 50; i++)
	{
		if (b[i].getIsbn() == isbn && b[i].getQuantity() != 0)
		{
			return i;//i is location of in book array
		}
		else if (b[i].getIsbn() == isbn && b[i].getQuantity() == 0)
		{
			return -2;//returned if quantity is zero
		}
	}

	return -1;//returned if book donot exist
}
void writeBook(Book* b)
{
	fstream out("booklist.txt", ios::out);
	for (int j = 0; j < 50; j++)//write books to File
	{
		if (b[j].getIsbn() != "" && (b[j].getIsbn().length() == 10 || b[j].getIsbn().length() == 13))
			out << b[j];
	}
	out.close();
}
void displayBook(Book* b)
{
	cout << endl;
	for (int j = 0; j < 50; j++)//display books to screen
	{
		if (b[j].getIsbn() != "")
			cout << b[j];
	}
}
void addBook(Book* b)//add a book to the book object array and file at the same time
{
	Book newBook;
	int pos;
	char yesNo;

	fstream outfile("booklist.txt", ios::out);
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Add Book");
	cout << endl << endl;
	cin.sync();
	cin >> newBook;
	for (int i = 0; i < 50; i++)
	{
		if (b[i].getIsbn() == "")
		{
			b[i] = newBook;
			pos = i;
			break;
		}
	}
	cout << "\nNew Book Info.......\n";
	cout << "\nISBN: " << b[pos].getIsbn() << endl
		<< "Book Title: " << b[pos].getTitle() << endl
		<< "Author: " << b[pos].getAuthor() << endl
		<< "Publisher: " << b[pos].getPublisher() << endl
		<< "Date Added: " << b[pos].getDate() << endl
		<< "Whole Sale Price: " << b[pos].getWholeSalePrice() << endl
		<< "Retail Price: " << b[pos].getRetailPrice() << endl
		<< "Quantity: " << b[pos].getQuantity() << endl;

	cout << "\nDo you wish to add book to inventory?[Y/N]: ";
	cin.clear();
	cin.sync();
	cin >> yesNo;
	if (yesNo == 'Y' || yesNo == 'y')
		outfile << newBook;
	else{
		b[pos].setIsbn("");
		b[pos].setTitle("");
	}
	outfile.close();

}
void removeBook(Book* b)//Delet book from inventory or prompt user if there are copies remaining
{
	string search;
	char yesNo;
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Remove Book");
	cout << endl << endl;
	cout << "Enter ISBN of book you want to remove: ";
	cin.sync();
	getline(cin, search, '\n');
	for (int i = 0; i < 50; i++)
	{

		if ((b[i].getIsbn() == search) && (b[i].getQuantity() == 0))
		{
			b[i].setIsbn(""); b[i].setTitle("");
			writeBook(b);
			break;
		}
		else if ((b[i].getIsbn() == search) && (b[i].getQuantity() > 0))
		{

			cout << "There are still " << b[i].getQuantity() << " copys remaining." << endl;
			cout << "Do you wish to Contiune [Y/N]: ";
			cin.sync();
			cin >> yesNo;
			if (yesNo == 'y' || yesNo == 'Y')
			{
				b[i].setIsbn("");
				writeBook(b);
				break;
			}
			else
				return;
		}
		else if (i == 49)
		{
			cout << "ISBN does not exist\n";
			system("pause");
			return;
		}
	}

	cout << "\nBook Succesfully Deleted.";
	system("pause");
}
void editBook(Book* b)
{
	string search, newInfo;
	int choice;

	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Edit Book");
	cout << endl << endl;
	cin.clear();
	cin.sync();
	cout << "\nEnter ISBN or Book Title: ";
	getline(cin, search);
	for (int i = 0; i < 50; i++)
	{
		if (search.compare(b[i].getTitle()) == 0 || search.compare(b[i].getIsbn()) == 0)
		{
			cout << "\nBook Found. " << endl;
			cout << "\nISBN: " << b[i].getIsbn() << endl
				<< "Book Title: " << b[i].getTitle() << endl
				<< "Author: " << b[i].getAuthor() << endl
				<< "Publisher: " << b[i].getPublisher() << endl
				<< "Date Added: " << b[i].getDate() << endl
				<< "Whole Sale Price: $" << b[i].getWholeSalePrice() << endl
				<< "Retail Price: $" << b[i].getRetailPrice() << endl
				<< "Quantity: " << b[i].getQuantity() << endl;
			cout << "\n\t\t\t1. Change ISBN " << endl
				<< "\t\t\t2. Change Book Title" << endl
				<< "\t\t\t3. Change Author" << endl
				<< "\t\t\t4. Change Publisher" << endl
				<< "\t\t\t5. Change Date Added" << endl
				<< "\t\t\t6. Change Whole Sale Price" << endl
				<< "\t\t\t7. Change Retail Price" << endl
				<< "\t\t\t8. Change Quantity" << endl;

			cin.sync();
			cout << "\n\t\t\t Enter your choice: ";
			cin >> choice;
			cin.sync();
			switch (choice)
			{
			case 1:
				do{
					cin.sync();
					cout << "Enter a 10 or 13 digit ISBN: ";
					getline(cin, newInfo);
					b[i].setIsbn(newInfo);
				} while (b[i].badIsbn());
				break;
			case 2:
				cout << "Enter new Book Title: ";
				getline(cin, newInfo);
				b[i].setTitle(newInfo);
				break;
			case 3:
				cout << "Enter new Author: ";
				getline(cin, newInfo);
				b[i].setAuthor(newInfo);
				break;
			case 4:
				cout << "Enter new Publisher: ";
				getline(cin, newInfo);
				b[i].setPublisher(newInfo);
				break;
			case 5:
				do{
					cin.sync();
					cout << "Enter new Date Added[mm/dd/yyyy]: ";
					getline(cin, newInfo);
					b[i].setDate(newInfo);
				} while (b[i].badDate());
				break;
			case 6:
				cout << "Enter new Whole Sale Price: ";
				getline(cin, newInfo);
				b[i].setWholeSalePrice(atof(newInfo.c_str()));
				break;
			case 7:
				cout << "Enter new Retail Price: ";
				getline(cin, newInfo);
				b[i].setRetailPrice(atof(newInfo.c_str()));
				break;
			case 8:
				cout << "Enter new Quantity: ";
				cin >> newInfo;
				b[i].setQuantity(atoi(newInfo.c_str()));
				break;
			default:
				cout << "Invalid choice!" << endl;
				system("pause>null");
				break;
			}
			writeBook(b);
			break;
		}
	}
}
string suggest(Book* b, string search)
{

	string checkstring;
	int p = 0;
	double count = 0;
	double ratio = 0;
	int w = 0;
	int closest = 0;
	double ratios[50];
	bool yesno;
	int copies = -1;
	int y;


	for (int i = 0; i < 50; i++)
	{

		if (search.compare(b[i].getTitle()) == 0 || search.compare(b[i].getIsbn()) == 0 || search.compare(b[i].getAuthor()) == 0)
		{
			copies = b[i].getQuantity();
		}
	}
	if (copies == -1)
	{
		while (p < 50)//searches for closest title but no pattern recognition. recognizes similarity through counter and character matching so not very accurate for many cases.
		{
			checkstring = b[p].getTitle();

			double size = search.length();
			for (int s = 0; s < b[p].getTitle().length(); s++)
			{

				if (search[w] == checkstring[s])
				{
					count++;
				}
				else if ((toupper(search[w]) == checkstring[s]) || (search[w] == toupper(checkstring[s])))
				{
					count++;
				}
				if (search[w] != '\0')
				{
					w++;
				}
			}

			ratio = (count / search.length());
			ratios[p] = ratio;

			p++;
			w = 0;
			count = 0;

			for (y = 0; y < 50; y++)
			{

				if ((ratios[y + 1] > ratios[y]) && (ratios[y + 1] > ratios[closest]))
				{
					closest = (y + 1);
				}

			}

		}
		cout << "did you mean: " << b[closest].getTitle() << "?" << endl;
		cout << "Enter '1' if YES or '0' if NO." << endl;;
		cin >> yesno;
		if (yesno == false)
		{
			cout << "Book could not be found please try again." << endl;
			return search;
		}
		else if (yesno == true)
		{
			search = b[closest].getIsbn();//set search input to corrected suggested title
			return search;
		}
	}
	return search;
}


int checkBook(Book *b, string search)
{
	int authorCount = 0;
	int copies = -1;
	search = suggest(b, search);

	for (int i = 0; i < 50; i++)
	{
		if (search.compare(b[i].getTitle()) == 0 || search.compare(b[i].getIsbn()) == 0 || search.compare(b[i].getAuthor()) == 0)
		{
			copies = b[i].getQuantity();
			authorCount++;
			cout << "\nISBN: " << b[i].getIsbn() << endl
				<< "Book Title: " << b[i].getTitle() << endl
				<< "Author: " << b[i].getAuthor() << endl
				<< "Publisher: " << b[i].getPublisher() << endl
				<< "Date Added: " << b[i].getDate() << endl
				<< "Whole Sale Price: " << b[i].getWholeSalePrice() << endl
				<< "Retail Price: " << b[i].getRetailPrice() << endl
				<< "Quantity: " << b[i].getQuantity() << endl;
		}
	}
	system("pause");
	return (authorCount > 1 ? authorCount : copies);//return number of books if author has multiple books listed
	//else return quantity for a book found or -1 if book doesn't
	//exist in the booklist(inventory)

}


void RetailValue(Book* b)
{
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Retail Value List");
	cout << endl << endl;
	double inventoryRetailValue = 0.0;
	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(26) << "RPrice" << setw(6) << "Qty." << endl;
	cout << "_____________________________________________________________________________________________________________________________________________________" << endl;


	for (int j = 0; j < 50; j++)//display books to screen
	{
		if (b[j].getIsbn() != "")
		{
			cout << left << setw(14) << b[j].getIsbn() << setw(42) << b[j].getTitle() << "$" << setw(10)
				<< b[j].getRetailPrice() << setw(2) << b[j].getQuantity() << endl;
			inventoryRetailValue = inventoryRetailValue + b[j].getRetailPrice() * b[j].getQuantity();
		}
	}
	cout << "\n_____________________________________________________________________________________________________________________________________________________" << endl;
	cout << "Inventory Retail value is: $" << inventoryRetailValue << endl;
	system("pause");

}
void wholesaleValue(Book* b)
{
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Wholesale Value List");
	cout << endl << endl;
	double inventoryWholesaleValue = 0.0;
	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(27) << "WSPrice" << setw(5) << "Qty." << endl;
	cout << "_____________________________________________________________________________________________________________________________________________________" << endl;


	for (int j = 0; j < 50; j++)//display books to screen
	{
		if (b[j].getIsbn() != "")
		{
			/*cout << b[j].getIsbn() << " " << b[j].getTitle() << ", $"
			<< b[j].getWholeSalePrice() << " "
			<< " " << b[j].getQuantity() << endl;*/

			cout << left << setw(14) << b[j].getIsbn() << setw(42) << b[j].getTitle() << "$" << setw(10)
				<< b[j].getWholeSalePrice() << setw(2) << b[j].getQuantity() << endl;

			inventoryWholesaleValue = inventoryWholesaleValue + b[j].getWholeSalePrice() * b[j].getQuantity();
		}
	}
	cout << "\n_____________________________________________________________________________________________________________________________________________________" << endl;
	cout << "Inventory wholesale value is: $" << inventoryWholesaleValue << endl;
	system("pause");

}
void quantityList(Book* b)//make new array and sort it by quantity, then cout array
{
	int position;
	Book highestQuantity;
	for (int i = 0; b[i].getIsbn() != ""; i++)
	{
		highestQuantity = b[i];
		position = i;
		for (int j = i + 1; b[j].getIsbn() != ""; j++)
		{
			if (b[j].getQuantity()> highestQuantity.getQuantity())//if b[j] has higher price than b[i]
			{
				highestQuantity = b[j];
				position = j;
			}
		}
		b[position] = b[i];
		b[i] = highestQuantity;
	}
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("List by Quantity");
	cout << endl << endl;


	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(33) << "Author" << setw(25)
		<< "Publisher" << setw(16) << "Date" << setw(14) << "WSPrice" << setw(10) << "RPrice" << setw(6) << "Qty." << endl;
	cout << "_________________________________________________________________________"
		"____________________________________________________________________________" << endl;


	displayBook(b);
	system("pause");
}
void inventoryList(Book* b)
{
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Inventory List");
	cout << endl << endl;

	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(33) << "Author" << setw(25)
		<< "Publisher" << setw(16) << "Date" << setw(14) << "WSPrice" << setw(10) << "RPrice" << setw(6) << "Qty." << endl;
	cout << "_________________________________________________________________________"
		"____________________________________________________________________________" << endl;
	displayBook(b);
	system("pause");
}
void priceList(Book* b)
{
	int position;
	Book highestPrice;
	for (int i = 0; b[i].getIsbn() != ""; i++)
	{
		highestPrice = b[i];
		position = i;
		for (int j = i + 1; b[j].getIsbn() != ""; j++)
		{
			if (b[j].getWholeSalePrice()> highestPrice.getWholeSalePrice())//if b[j] has higher price than b[i]
			{
				highestPrice = b[j];
				position = j;
			}
		}
		b[position] = b[i];
		b[i] = highestPrice;
	}
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Price List");
	cout << endl << endl;

	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(33) << "Author" << setw(25)
		<< "Publisher" << setw(16) << "Date" << setw(14) << "WSPrice" << setw(10) << "RPrice" << setw(6) << "Qty." << endl;
	cout << "_________________________________________________________________________"
		"____________________________________________________________________________" << endl;

	displayBook(b);
	system("pause");

}
void ageSort(Book* b)
{
	int position;
	Book old;
	for (int i = 0; b[i].getIsbn() != ""; i++)
	{
		old = b[i];
		position = i;
		for (int j = i + 1; b[j].getIsbn() != ""; j++)
		{
			if (b[j]>old == 1)//if b[j] is older than b[i]
			{
				old = b[j];
				position = j;
			}
		}
		b[position] = b[i];
		b[i] = old;
	}
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Age List");
	cout << endl << endl;

	cout << right << setw(9) << "ISBN" << setw(27) << "Title" << setw(33) << "Author" << setw(25)
		<< "Publisher" << setw(16) << "Date" << setw(14) << "WSPrice" << setw(10) << "RPrice" << setw(6) << "Qty." << endl;
	cout << "_________________________________________________________________________"
		"____________________________________________________________________________" << endl;

	displayBook(b);
	system("pause");
}
void transactionList()
{

	string info;
	fstream infile("transactionLog.txt", ios::in);
	system("cls");
	centerstring("Serendipity Booksellers");
	centerstring("Transaction List");
	cout << endl;
	while (infile)
	{
		getline(infile, info, '\n');
		cout << endl << info;
	}
	system("pause");
}
void cashier(Book* b)
{
	bool buyagain = true;
	//open the transactionLog file
	fstream outfile("transactionLog.txt", ios::app);

	while (buyagain == true)
	{
		string isbn[50];
		int qty[50], i;
		double price[50];
		string title[50];
		bool nextBook = true;//allow user to buy another book after the first one
		bool quantitycheck = false;//for check loop if we have enough quanity to sell
		bool fail = true;
		double total = 0, subTotal = 0, tax = 0;
		double paid;
		i = 0;
		double due = 0;
		int location[50];//storing array locations of corresponding book being sold 
		system("cls");
		centerstring("Serendipity Booksellers");
		centerstring("Cashier");

		cout << endl;

		while (nextBook == true)
		{
			quantitycheck = false;
			cout << "\nEnter ISBN or type '~': ";//or change to escape key
			fail = true;
			while (fail){
				try {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					getline(cin, isbn[i]);
					if (isbn[i].length() != 10 && isbn[i].length() != 13 && isbn[i] != "~" && isbn[i] != "`")
						throw "Invalid input. Please enter a 10 or 13 digit isbn: ";
					else
						fail = false;
				}
				catch (char* error) {
					cout << error;
				}
			}

			if (isbn[i] == "~")// need to add error check for correct input
			{
				nextBook = false;
			}
			else if (locateBook(b, isbn[i]) == -1)//need to be able to locate book (return -1 if book not found)
			{
				cout << "Book was not found." << endl;
			}
			else if (locateBook(b, isbn[i]) == -2)//need to be able to locate book (if book out of stock)
			{
				cout << "Book is out of stock." << endl;
			}

			else
			{
				while (quantitycheck == false)
				{
					cout << "Enter number of copies: ";
					fail = true;
					while (fail){
						try {
							cin >> qty[i];
							if (cin.fail()){
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								throw "Invalid input. Enter an integer: ";
							}
							else if (qty[i] < 0)
								throw "Invalid input. Please enter a positive number: ";
							else
								fail = false;
						}
						catch (char* error) {
							cout << error;
						}
					}

					if (qty[i] > b[locateBook(b, isbn[i])].getQuantity())//check if inventory has enough quantity for transaction
					{
						if (b[locateBook(b, isbn[i])].getQuantity() > 1)
							cout << "Not enough in inventory. We only have " << b[locateBook(b, isbn[i])].getQuantity()
							<< " copies. Enter a smaller amount: ";
						else
							cout << "Not enough in inventory. We only have " << b[locateBook(b, isbn[i])].getQuantity()
							<< " copies. Enter a smaller amount: ";

					}
					else
					{
						title[i] = b[locateBook(b, isbn[i])].getTitle();
						price[i] = b[locateBook(b, isbn[i])].getRetailPrice();
						system("cls");
						centerstring("Serendipity Booksellers");
						centerstring("Cashier");
						cout << "\n" << right << setw(4) << "Qty." << setw(10) << "ISBN" << setw(29) << "Title" << setw(24) << "Price" << setw(8) << "Total" << endl;
						cout << "________________________________________________________________________________ " << endl;//output layout isnt consistent due to changing title lengths
						for (int j = 0; j <= i; j++)
						{
							cout << endl << left << setw(5) << qty[j] << setw(16) << isbn[j] << setw(42) << title[j] << setw(7) << price[j] << setw(10) << fixed << setprecision(2) << (qty[j] * price[j]) << endl;
							outfile << endl << left << setw(5) << qty[j] << setw(16) << isbn[j] << setw(42) << title[j] << setw(7) << price[j] << setw(10) << fixed << setprecision(2) << (qty[j] * price[j]);
						}

						b[locateBook(b, isbn[i])].setQuantity(b[locateBook(b, isbn[i])].getQuantity() - qty[i]);//decrease quantity of book by amount sold
						i++;
						quantitycheck = true;
					}
				}
			}
		}

		for (int z = 0; z < i; z++)
		{
			subTotal += (price[z] * qty[z]);//adds up totals for transaction
		}
		tax += 0.095*subTotal;
		total = tax + subTotal;
		writeBook(b);

		cout << right;
		cout << setw(70) << "Sub-Total is: $" << fixed << setprecision(2) << subTotal << "." << endl;
		cout << setw(70) << "Tax amount is: $" << fixed << setprecision(2) << tax << "." << endl;
		cout << setw(70) << "Total price is: $" << fixed << setprecision(2) << total << "." << endl;

		outfile << right << endl << endl;
		outfile << setw(70) << "Sub-Total is: $" << fixed << setprecision(2) << subTotal << "." << endl;
		outfile << setw(70) << "Tax amount is: $" << fixed << setprecision(2) << tax << "." << endl;
		outfile << setw(70) << "Total price is: $" << fixed << setprecision(2) << total << "." << endl;

		if (total > 0)
		{
			while (due < total)
			{
				cout << setw(70) << "Enter amount paid: $";
				outfile << setw(70) << "Amount paid: $";
				fail = true;
				while (fail){
					try {
						cin >> paid;
						if (cin.fail()){
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							throw "Invalid input. Enter a double: ";
						}
						else if (paid < 0)
							throw "Invalid input. Please enter a positive number: ";
						else
							fail = false;
					}
					catch (char* error) {
						cout << error;
					}
				}
				outfile << paid << endl;
				due += paid;
				cin.ignore();
				if (due < total)
				{
					cout << endl << setw(70) << "Amount still due: $" << fixed << setprecision(2) << total - due << "." << endl;
					outfile << endl << setw(70) << "Amount still due: $" << fixed << setprecision(2) << total - due << "." << endl;
				}
				else if (due > total)
				{
					cout << setw(70) << "Change due is: $" << fixed << setprecision(2) << due - total << "." << endl;
					outfile << setw(70) << "Change due is: $" << fixed << setprecision(2) << due - total << "." << endl;
					outfile << "_____________________________________________________________________________________" << endl;
				}
			}
		}
		cin.clear();

		cout << "Press '1' to for next transaction or '0' to exit. ";
		fail = true;
		while (fail){
			try {
				cin >> buyagain;
				if (cin.fail()){
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw "Invalid input. Enter 1 or 0: ";
				}
				else if (buyagain != 0 && buyagain != 1)
					throw "Invalid input. Enter 1 or 0: ";
				else
					fail = false;
			}
			catch (char* error) {
				cout << error;
			}
		}
	}
	cin.ignore();
	outfile.close();
	system("pause");

}


void inventoryDatabaseModule(Book* b, char select2)
{
	fstream infile("booklist.txt", ios::app);
	infile.open("booklist.txt");



	while (select2)
	{

		system("cls");
		centerstring("Serendipity Booksellers");
		centerstring("Inventory Database");
		cout << "\n\t\t\t\t\t\t 1. Look Up a Book\n"
			<< "\t\t\t\t\t\t 2. Add a Book\n"
			<< "\t\t\t\t\t\t 3. Edit a Book's Record\n"
			<< "\t\t\t\t\t\t 4. Delete a Book\n"
			<< "\t\t\t\t\t\t 5. Return to Main Menu" << endl;
		cout << "\n\t\t\t\t\t\t Enter your choice: ";
		cin >> select2;
		system("cls");
		switch (select2)
		{
		case '1': //Look Up a Book
		{
			int check;
			string search;
			cout << "\nEnter Search Term[ISBN, book title, Author]: ";
			cin.ignore();
			getline(cin, search);
			check = checkBook(b, search);
			if (check>0)//check if book is available
				cout << "\nBook available\n";
			else if (check == 0)

				cout << "\nNo Copy available(out of stock).Sorry!\n";
			system("pause");
			break;
		}
		case '2': //Add a Book
		{
			infile.close();
			addBook(b);
			displayBook(b);
			system("pause");
			break;
		}
		case '3': //Edit a book
		{
			cin.ignore();
			infile.close();
			editBook(b);
			infile.open("booklist.txt");
			for (int j = 0; j < 50; j++)//write books to file
			{
				if (b[j].getIsbn() != "")
					infile << b[j];
			}
			break;
		}
		case '4'://Remove a book completely
		{
			cin.ignore();
			removeBook(b);
			break;
		}
		case '5': //Return to Main Menu
		{

			select2 = '\0';
			//goto FirstMenu;


		}
		}//Closing bracket inner switch statement
	}//closing bracket inner while loop
	infile.close();
}

void reportModule(Book* b, char select3)
{
	while (select3)
	{
		system("cls");
		centerstring("Serendipity Booksellers");
		centerstring("Reports");
		cout << "\n\n\n\t\t\t\t\t\t 1. Inventory Listing\n"
			<< "\t\t\t\t\t\t 2. Inventory Wholesale Value\n"
			<< "\t\t\t\t\t\t 3. Inventory Retail Value\n"
			<< "\t\t\t\t\t\t 4. Listing by Quantity\n"
			<< "\t\t\t\t\t\t 5. Listing by Cost\n"
			<< "\t\t\t\t\t\t 6. Listing by Age\n"
			<< "\t\t\t\t\t\t 7. Transaction List\n"
			<< "\t\t\t\t\t\t 8. Return to Main Menu" << endl;
		cout << "\n\t\t\t\t\t\t Enter your choice:";
		cin.sync();
		cin >> select3;

		switch (select3)
		{
		case '1'://Inventory List
			inventoryList(b);
			break;

		case '2'://Inventory Wholesale Value
			wholesaleValue(b);
			break;

		case '3'://Inventory Retail Value
			RetailValue(b);
			break;

		case '4'://List by Quantity
			quantityList(b);
			break;

		case '5'://List by Cost
			priceList(b);
			break;

		case '6'://List by Age
			ageSort(b);
			break;
		case '7'://List by Age
			transactionList();
			break;

		case '8'://Return to Main Menu

			select3 = '\0';
			//goto FirstMenu;
			break;
		}
	}//While closing bracket

}

int main()
{
	cout << fixed << setprecision(2);
	const int SIZE = 50;
	string  search;
	Book b[SIZE];
	string info[1000];
	int i = 0;
	int k = 0;
	fstream infile("booklist.txt", ios::in | ios::app);
	while (infile)//read file and asssign values to book objects
	{
		infile >> b[i++];
	}
	infile.close();

	char select = '1';
	char select2 = '1';
	char select3 = '1';
	while (select)
	{
		system("cls");
		//FirstMenu:
		centerstring("Serendipity Booksellers");
		centerstring("Main Menu");
		cout << endl;
		cout << "\n\t\t\t\t\t\t 1. Cashier Module\n"
			<< "\t\t\t\t\t\t 2. Inventory Database Module\n"
			<< "\t\t\t\t\t\t 3. Report Module\n"
			<< "\t\t\t\t\t\t 4. Exit." << endl;
		cout << "\n\t\t\t\t\t\t Enter your choice: ";
		cin.sync();//reset cin stream
		cin >> select;
		system("cls");

		switch (select)
		{
		case '1':
			cashier(b);
			break;

		case '2'://Inventory Database Module
			inventoryDatabaseModule(b, select2);
			break;

		case '3': //Report Module
			reportModule(b, select3);
			break;

		case '4': //Exit
			cout << "\nThank you For Using Our System.\n" << endl;
			select = '\0';
			break;

		default:
			cout << "\nPlease Select a Valid Choice! Hit ENTER to Continue.";
			break;
		}

	}

	system("pause");
	return 0;

}



