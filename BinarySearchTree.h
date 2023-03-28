#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Node.h"
#include <exception>

template <typename T>
class BinarySearchTree
{
public:

	//https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

	BinarySearchTree();
	~BinarySearchTree();
	void Insert(T* inval, Node<T>* parent);
	void Remove(T* inval);
	//these functions Remove should rebalance if necessary
	bool Find(T* inval, Node<T>* parent);
	Node<T>* FindTransverse(T* inval, Node<T>* parent);
	void GetAllAscending();   //key is string,  count is data//  sort by string
	void GetAllDescending();
	void EmptyTree();
	int Size();
	void Print(Node<T>* toprint);

	//these are used in recurssion where yah ahve to keep track of the parent and grandparent
	//Node<T>* BinarySearchTree<T>::FindTransverseParent(T* inval, Node<T>* parent);
	Node<T>* FindTransverseFamily(T* inval, Node<T>* grandparent, Node<T>* parent, Node<T>* child);

	int GetHeight(Node<T>* current);   //This does the rebalancing
	void RotateLeft(Node<T>* parent, Node<T>* pivot);  // change arguments to be more appropriate
	void RotateRight(Node<T>* parent, Node<T>* pivot);
	void RotateLeftRight(Node<T>* parent, Node<T>* pivot);
	void RotateRightLeft(Node<T>* parent, Node<T>* pivot);


	class TreeException : public exception {
	public:
		TreeException(const char* message) : msg_(message) {}
		const char* what() const noexcept { return msg_.c_str(); }
	private:
		string msg_;
	};

	private:
		Node<T>* root;
	/*
	private:
		struct Node
		{
			int value;
			Node* left;
			Node* right;
		};
		Node* root;
		void insert(int value, Node* node);
		void remove(int value, Node* node);
		bool search(int value, Node* node);
		void print(Node* node);
		void destroy(Node* node);
		Node* findMin(Node* node);
		Node* findMax(Node* node);
		Node* removeMin(Node* node);
		Node* removeMax(Node* node);
		Node* remove(int value, Node* node);
		Node* find(int value, Node* node);
		Node* findParent(int value, Node* node);
		Node* findMinParent(Node* node);
		Node* findMaxParent(Node* node);
	};
	*/
};

#endif 