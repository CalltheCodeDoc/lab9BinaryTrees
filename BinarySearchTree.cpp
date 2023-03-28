#include "BinarySearchTree.h"
#include <iostream>

template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
	root=nullptr;
}
template <typename T>
BinarySearchTree<T>::~BinarySearchTree() { }
template <typename T>
void BinarySearchTree<T>::Insert(T* inval, Node<T>* parent) {
	//inserting options:
	//head->right->right
	//head->right->left
	//head->left->right
	//head->left->left

	//recursion
	if(root == nullptr) {
		root = new Node<T>(inval);
		return;
	}
	elseif(*inval->key > *parent->key){
		Insert(inval, parent->right);
	}
	else {
		Insert(inval, parent->left);
	}
	//need to manage other parameters here like
	//height
	//balance
	//level
	//size or count

}
template <typename T>
void BinarySearchTree<T>::Remove(T* inval) {

//these functions Remove should rebalance if necessary


}


template <typename T>
bool BinarySearchTree<T>::Find(T* inval, Node<T>* parent) {
	//recurssion
	if (parent == nullptr) {
		return false;
	}
	else if (*parent->key == inval) {
		return true;
	}
	else if (inval > *parent->key) {
		return FindTransverse(inval, parent->right);
	}
	else {
		return FindTransverse(inval, parent->left);
	}

}
template <typename T>
Node<T>* BinarySearchTree<T>::FindTransverse(T* inval, Node<T>* parent) {
	//recurssion
	if (parent == nullptr) {
		return nullptr;
	}
	else if (*parent->key == inval) {
		return parent;
			}
	else if (inval > *parent->key) {
		return FindTransverse(inval, parent->right);
	}
	else {
		return FindTransverse(inval, parent->left);
	}

}
template <typename T>
void BinarySearchTree<T>::GetAllAscending() { }
template <typename T>
void BinarySearchTree<T>::GetAllDescending() { }
template <typename T>
void BinarySearchTree<T>::EmptyTree() { }
template <typename T>
int BinarySearchTree<T>::Size() { }
template <typename T>
void BinarySearchTree<T>::Print(Node<T>* toprint) {
	if (toprint == null) return;
	cout << toprint->data << " ( ";
	if (toprint->left != nullptr) {
		cout << toprint->left->data;
	}
	cout << " ,";
	if(toprint->right!=nullptr)
		cout << toprint->right->data;
	cout << " ) " << endl;
	Print(toprint->left);
	Print(toprint->right);

}

template <typename T>
int BinarySearchTree<T>::GetHeight(Node<T>* current) { 
	if(current==nullptr)
		return 0;
	int L = GetHeight(current->left);
	int R = GetHeight(current->right);
	if(L==nullptr && R==nullptr)
		return 1;
	if (L > R) {
		return 2 + 1;  
	}
	else
	{
		return R + 1; 
	}
	//inserting options:
	//head->right->right
	//head->right->left
	//head->left->right
	//head->left->left
}   //This does the rebalancing
template <typename T>
void BinarySearchTree<T>::RotateLeft(Node<T>* parent, Node<T>* pivot) { }
template <typename T>
void BinarySearchTree<T>::RotateRight(Node<T>* parent, Node<T>* pivot) { 
	//children
	if (children) {

		parent->left = parent->left->left;
		parent->left->right = pivot->left->right;
		pivot->left->right = pivot;
	
	}


	if(!children){ 
	
		parent->left = parent->left->left;
		parent->left->right = pivot;
		pivot->left = nullptr;
	
	}	
	
}
template <typename T>
void BinarySearchTree<T>::RotateLeftRight(Node<T>* parent, Node<T>* pivot) { }
template <typename T>
void BinarySearchTree<T>::RotateRightLeft(Node<T>* parent, Node<T>* pivot) { 
//this is one type, for all children
	//need to make a type for no children
	//need to make a type for one child
	parent->right->left;
	pivot->right->left = parent->left->right;
	parent->left->right = pivot->right;
	//pivot->right->left = nullptr;
	pivot->right = parent->left->left;
	parent->left->left = pivot;

}

