#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "Node.h"

using namespace std;



//operator overload to compare items in tree, dunno if have to make yeah another separate class for this
//bool operator >(InventoryItem& const other);
//bool operator <(InventoryItem& const other);
//bool operator ==(InventoryItem& const other);
//friend ostream& operator<<(ostream& out, const InventoryItem& other);


//**********************************************************************************************************
//CODE BELOW IS HW1 CODE NOT YET ADJUSTED FOR LAB 9
const int LETTER_NUM = 26;
int main()
{
	string answer;
	do {
		// Ask the user for the name of the file to be processed. 
		cout << "Enter the name of the file to be processed: ";
		string filename;
		getline(cin, filename);
		//Attempt to open the file of the given name.If unsuccessful, it should output an error message
		//and prompt the user to enter another file name.
		ifstream inFile;
		inFile.open(filename, ios::in);
		while (!inFile)
		{
			cout << "Error: unable to open the file. Enter another file name: ";
			getline(cin, filename);
			inFile.open(filename, ios::in);
		}
		/*With the file open, read into a Structure :
		a.Title
		b.Author full name(the name is stored in the file as Firstand Last name with a
		space between)
		c.Word Count(total number of words in the book contents.A word is one or more
			letters(not counting punctuation) separated by a space so ice cream is considered
			2 words)
		d.Letter frequency(this is the number of times each letter has been encountered in
			the book contents)
		e.Line Count(count of new line characters in the contents section)*/
		struct Book
		{
			string title;
			string fullName;
			int wordCount;
			double letterFreqs[LETTER_NUM];
			int lineCount;
		};
		Book book;
		book.wordCount = 0;
		book.lineCount = 0;
		getline(inFile, book.title);
		getline(inFile, book.fullName);
		inFile.ignore(9, '\n');
		while (inFile)
		{
			string word;
			inFile >> word;
			if (word != "")
			{
				book.wordCount++;
			}
		}
		inFile.clear();
		inFile.seekg(0L, ios::beg);
		int letterCounts[LETTER_NUM] = { 0 };
		inFile.ignore(100, ':');
		inFile.ignore(1, '\n');
		while (inFile)
		{
			char letter;
			inFile.get(letter);
			if (isupper(letter))
			{
				letterCounts[static_cast<int>(letter) - static_cast<int>('A')]++;
			}
			else if (islower(letter))
			{
				letterCounts[static_cast<int>(letter) - static_cast<int>('a')]++;
			}
			else
			{
			}
		}
		int total = 0;
		for (int i = 0; i < LETTER_NUM; i++)
		{
			total += letterCounts[i];
		}
		for (int i = 0; i < LETTER_NUM; i++)
		{
			book.letterFreqs[i] = letterCounts[i] / static_cast<double>(total);
		}
		inFile.clear();
		inFile.seekg(0L, ios::beg);
		inFile.ignore(100, ':');
		inFile.ignore(1, '\n');
		while (inFile)
		{
			string line;
			getline(inFile, line);
			if (line != "")
			{
				book.lineCount++;
			}
		}
		inFile.close();
		/*Save this information in the file CardCatalog.txt
	   a.If the file doesn’t exist, create it.
	   b.If the file does exist, append to it.
	   c.Leave a blank line between each card catalog entry.
	   d.The file should be human readable such as (is should be similar but not
		necessarily the same as the following) :
		Title: Moby Dick
		Full Author : Herman Melville
		Author First Name : Herman
		Author Last Name : Melville
		Word count : 375
		Line count : 17*/
		ofstream outFile;
		outFile.open("CardCatalog.txt", ios::app);
		outFile << "Title : " << book.title << endl;
		outFile << "Full Author : " << book.fullName << endl;
		int index = book.fullName.find(' ');
		string firstName = book.fullName.substr(0, index);
		string lastName = book.fullName.substr(index + 1);
		outFile << "Author First Name : " << firstName << endl;
		outFile << "Author Last Name : " << lastName << endl;
		outFile << "Word count : " << book.wordCount << endl;
		outFile << "Line count : " << book.lineCount << endl << endl;
		outFile.close();
		/*5. Ask the user if they want to see the letter frequency.If they agree, it should look likeii :
		Moby Dick letter frequency :
		a: 0.0762 %
		b : 0.0 %
		c : 0.0253 %
		d : 0.0405 %*/
		cout << "Do you want to see the letter frequency? Enter \"yes\" or \"no\": ";
		//string answer;
		cin >> answer;
		while (answer != "yes" && answer != "no")
		{
			cout << "Error: please enter \"yes\" or \"no\": " << endl;
			cin >> answer;
		}
		if (answer == "yes")
		{
			for (int i = 0; i < LETTER_NUM; i++)
			{
				cout << char(static_cast<int>('a') + i) << ": " << book.letterFreqs[i] << endl;
			}
		}

		/*6. Ask the user if they wish to process another book.If they do, repeat requirement 2.  If
		they don’t, program should quit.This should not add to previous results*/


		cout << "Do you want to process another book? (Enter 'yes' or 'no'): ";
		cin >> answer;


		while (answer != "yes" && answer != "no")
		{
			cout << "Error: please enter \"yes\" or \"no\": " << endl;
			cin >> answer;
		}
		cin.ignore(1, '\n');
	} while (answer == "yes");

	return 0;
}