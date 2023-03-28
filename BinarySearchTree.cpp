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
	//this is inefficient
	Node<T>* tempgrandchild = FindTransverse(inval, root);
	Node<T>* temp = FindTransverseFamily(inval, root, nullptr, nullptr);
	bool children = false;
	if (tempgrandchild == nullptr) {
		return; //nothing to remove   SHould PRINT OUT A THROW EXCEPTION BUT KEEP PROGRAM RUNNING
	}
	if (temp == nullptr) {
		return;  //nothing to remove   SHould PRINT OUT A THROW EXCEPTION BUT KEEP PROGRAM RUNNING
	}
	if (tempgrandchild->right != nullptr||tempgrandchild->left!=nullptr) {
		children = true;
	}
	
	else {
		//remove
		if (children) {//
			//have to reinsert children in tree
		}
		else {//nochildren

			//**********************************  THIS IS TOO MESSY, BETTER TO USE RECURSSION
			// ********************************* YEAH SCREW THIS
			// ******************************  RECURSION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// 
			//temp
				//first if only activates if temp is the root and tempgrandchild= temp
				//if this isnt the case then there is a bug here
			 if (*temp->key == *inval) {
				 root == nullptr;
				 delete temp->key;
				 delete temp->data;
				 delete temp;
				 return;
			}
			else if (*inval > *temp->key) {
				 if (*temp->right->key == *inval) {
					 
					 delete temp->right->key;
					 delete temp->right->data;
					 //might mess up here **********************************************
					 //maybe make second temp, then change temp->right to null ptr then delete second temp
					 delete temp->right;
					 temp->right == nullptr;
					 return;
				 }
				 else if (*inval > *temp->right->key) {
					 if (*temp->right->right->key == *inval) {
						 
						 delete temp->right->right->key;
						 delete temp->right->right->data;
						 delete temp->right->right;
						 temp->right->right == nullptr;
						 return;
					 }
					 else {
						 delete temp->right->left->key;
						 delete temp->right->left->data;
						 delete temp->right->left;
						 temp->right->left == nullptr;
						 return;
					 }
				 }
				 else {
					 //dont need this else
				 }
			}
			else {
				 if (*temp->left->key == *inval) {

					 delete temp->left->key;
					 delete temp->left->data;
					 //might mess up here **********************************************
					 //maybe make second temp, then change temp->right to null ptr then delete second temp
					 delete temp->left;
					 temp->left == nullptr;
					 return;
				 }
				 else if (*inval > *temp->left->key) {
					 if (*temp->left->right->key == *inval) {

						 delete temp->left->right->key;
						 delete temp->left->right->data;
						 delete temp->left->right;
						 temp->left->right == nullptr;
						 return;
					 }
					 else {
						 delete temp->left->left->key;
						 delete temp->left->left->data;
						 delete temp->left->left;
						 temp->left->left == nullptr;
						 return;
					 }
				 }
				 else {
					 //dont need this else
				 }
			}
				//problem wiht this is yah need to work with parents and grandparents
				//in both the if and else case
				//the parent needs to be rewritten to point to nullptr while the
				//child needs to be deleted
				//use recursion remove functions
				
		}
		//rebalance
	}

}


template <typename T>
bool BinarySearchTree<T>::Find(T* inval, Node<T>* parent) {
	//recurssion
	if (parent == nullptr) {
		return false;
	}
	else if (*parent->key == *inval) {
		return true;
	}
	else if (*inval > *parent->key) {
		return Find(*inval, parent->right);
	}
	else {
		return Find(*inval, parent->left);
	}

}
template <typename T>
Node<T>* BinarySearchTree<T>::FindTransverse(T* inval, Node<T>* parent) {
	//recurssion
	if (parent == nullptr) {
		return nullptr;
	}
	else if (*parent->key == *inval) {
		return parent;
			}
	else if (*inval > *parent->key) {
		return FindTransverse(*inval, parent->right);
	}
	else {
		return FindTransverse(*inval, parent->left);
	}

}
template <typename T>
Node<T>* BinarySearchTree<T>::FindTransverseFamily(T* inval, Node<T>* grandparent, Node<T>* parent, Node<T>* child) {
	//recurssion
	//initiate with grandparent as root, and parent and child as nullptrs
	//slowly fill in parent and child as you go down the tree

	//************************************************************
	//THIS DOESN't RETURN THE NODE ITSELF WHERE THE VALUE IS AT
	//IT RETURNS THE GRANDPARENT OF THE NODE WHERE THE VALUE IS AT
	//************************************************************
	//GOTTA FIGURE OUT HOW TO DEAL WITH THIS WITH FUNCTIONS THAT CALL THIS
	//************************************************************

	//should i return the grandparent or a vector of the family?
	if (parent == nullptr && child == nullptr) {
		//this basically says we are at the root, parent and child of the current search position don't necessarily
		//equal null, 
		//but once we check if the parent and or child of the value supplied by grandparent is nullptr
		//then there are no more children to check
		if (grandparent == nullptr) {
			return nullptr; //not found
		}
		else if (*grandparent->key == inval) {
			return grandparent;
		}
		else if (inval > *grandparent->key) {
			return FindTransverseFamily(inval, grandparent, grandparent->right, nullptr);
			//return FindTransverse(inval, grandparent->right);
		}
		else {
			return FindTransverseFamily(inval, grandparent, grandparent->left, nullptr);
			//return FindTransverse(inval, parent->left);
		}
	}
	else if (child == nullptr) {
		if (parent == nullptr) {
			return nullptr; //not found
		}
		else if (*parent->key == *inval) {
			return grandparent;
		}
		else if (*inval > *parent->key) {
			return FindTransverseFamily(inval, grandparent, parent, parent->right);
			//return FindTransverse(inval, grandparent->right);
		}
		else {
			return FindTransverseFamily(inval, grandparent, parent, parent->left);
			//return FindTransverse(inval, parent->left);
		}
	}
	else {
		if (child == nullptr) {
			return nullptr; //not found
		}
		else if (*child->key == *inval) {
			return grandparent;
		}
		else if (*inval > *child->key) {
			return FindTransverseFamily(inval, parent, child, child->right);
			//return FindTransverse(inval, grandparent->right);
		}
		else {
			return FindTransverseFamily(inval, parent, child, child->left);
			//return FindTransverse(inval, parent->left);

		}


	}
}
/*
template <typename T>
Node<T>* BinarySearchTree<T>::FindTransverseGrandParent(T* inval, Node<T>* parent) {
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
*/
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

