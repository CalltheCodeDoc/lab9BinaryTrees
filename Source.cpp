#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "Node.h"
#include "Node.cpp"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using namespace std;



//operator overload to compare items in tree, dunno if have to make yeah another separate class for this
//bool operator >(InventoryItem& const other);
//bool operator <(InventoryItem& const other);
//bool operator ==(InventoryItem& const other);
//friend ostream& operator<<(ostream& out, const InventoryItem& other);
bool retesting = false;
bool to_test = true;

int main()
{


	//debug code block

	BinarySearchTree<int>* Tree=new BinarySearchTree<int>();
	Tree->Insert(new int(25), Tree->root);
	Tree->Insert(new int(20), Tree->root);
	Tree->Insert(new int(45), Tree->root);
	Tree->Insert(new int(13), Tree->root);
	Tree->Insert(new int(100), Tree->root);
	Tree->Insert(new int(6), Tree->root);
	Tree->Insert(new int(17), Tree->root);
	Tree->Insert(new int(30), Tree->root);
	Tree->Insert(new int(31), Tree->root);
	Tree->Insert(new int(5), Tree->root);
	Tree->Insert(new int(8), Tree->root);
	Tree->Insert(new int(1), Tree->root);
	Tree->Print(Tree->root);

	//cout << endl << endl << endl;
	//cout << "Number of nodes in tree are: " << Tree->Size(0, Tree->root) << endl;

	//Node<int>** arg = Tree->GetAllAscending();
	Node<int>** arg = Tree->GetAllDescending();
	//cout << "Size of: array: "<<sizeof(arg) << endl;
	for (int i = 0; i < Tree->Size(0, Tree->root); i++) {
		cout << *arg[i]->key << endl;
	}

	if (false) {
		//seems to work, it has a fail case, but the fail case catch happens outside of the function
		//not good to test the fail case without duplicating the external catching mechanism
		cout << endl << endl << endl;
		Node<int>* temp = Tree->FindMinimum(Tree->root, Tree->root->left);
		Tree->Print(temp);

		cout << endl << endl << endl;
		temp = Tree->FindMinimum(Tree->root->right, Tree->root->right->left);
		Tree->Print(temp);

		cout << endl << endl << endl;
		temp = Tree->FindMinimum(Tree->root->left, Tree->root->left);
		Tree->Print(temp);

		cout << endl << endl << endl;
		temp = Tree->FindMinimum(Tree->root, Tree->root->left);
		Tree->Print(temp);
	}


	if (retesting) {
		cout << endl << endl << endl;
		Node<int>* temp = Tree->FindTransverseFamily(new int(1), Tree->root, nullptr, nullptr);
		Tree->Print(temp);
		cout << endl << endl << endl;
		temp = Tree->FindTransverseFamily(new int(100), Tree->root, nullptr, nullptr);
		Tree->Print(temp);
		cout << endl << endl << endl;
		temp = Tree->FindTransverseFamily(new int(45), Tree->root, nullptr, nullptr);
		Tree->Print(temp);
		cout << endl << endl << endl;
		temp = Tree->FindTransverseFamily(new int(8), Tree->root, nullptr, nullptr);
		Tree->Print(temp);
		cout << endl << endl << endl;
		temp = Tree->FindTransverseFamily(new int(25), Tree->root, nullptr, nullptr);
		Tree->Print(temp);
	}

	if (to_test) {
		//Doesn't work, remove function is broken
		Tree->remove(new int(5));

		Tree->Print(Tree->root);
		//so far only thing that half works is removing 31 off the right branch, but the right branch is fucked up in display
		//errors up at right->key
		//removing 8 works for the first root children but not past that
		//removing 17 errors up all but the root
		//removing 1 errors on leftkey of left child of root
	}


	return 0;
}

//**********************************************************************************************************
//CODE BELOW IS HW1 CODE NOT YET ADJUSTED FOR LAB 9
/*
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
*/