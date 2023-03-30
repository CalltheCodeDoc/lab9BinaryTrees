#include "BinarySearchTree.h"
#include <iostream>

using namespace std;
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

	//************************************************************
	//duplicate values are always put on leftside
	// what if that first node is  removed, will it still find the duplicate value?
	// //i think so if rebalancing is handled right
	// BUT THE STANDARD FOR THIS CODE IS ALL DUPLICATE VALUES GET PLACED ON THE LEFT
	//************************************************************
	if(root == nullptr) {
		root = new Node<T>(inval);
		return;
	}
	else if(*inval > *parent->key){
		if (parent->right == nullptr) {
			parent->right = new Node<T>(inval);
			return;
		}
		Insert(inval, parent->right);
	}
	else {
		if (parent->left == nullptr) {
			parent->left = new Node<T>(inval);
			return;
		}
		Insert(inval, parent->left);
	}
	//need to manage other parameters here like
	// 
	//height
	//balance
	//level
	//size or count
	//
	//NEED TO REBALANCE HERE TOOO
}
template <typename T>
void BinarySearchTree<T>::Remove(T* inval) {

	//these functions Remove should rebalance if necessary
		//this is inefficient
	//Node<T>* tempgrandchild = FindTransverse(inval, root);
	//bool children = false;
	Node<T>* temp = FindTransverseFamily(inval, root, nullptr, nullptr);
	bool exception = false;
	if (temp == nullptr) {
		return; //nothing to remove   SHould PRINT OUT A THROW EXCEPTION BUT KEEP PROGRAM RUNNING
	}
	else if (temp->isTarget) {
		if (temp->left == nullptr && temp->right == nullptr) {
			//target is root and is the only node in tree
			temp->isTarget = false;
			temp->Target = nullptr;
			root = nullptr;
			delete temp;    //********************** remove if u dont want to delete but want to fetch it
			//no rebalancing necessary here
		}
		else {
			//TODO
			//what to do if root has children
			//rebalance? or just remove and let rebalancing handle it? or just remove and dont rebalance?

			if (temp->Target->left != nullptr&& temp->Target->right == nullptr) {
				root = temp->Target->left;
				//temp->Target->left = nullptr;
				//below line is unnecessary
				//temp->Target->left->right= temp->right //THIS ONLY WORKS IF target has no children
					//TO DO
					//could put conditionals where if temp->right and temp->Target->left->right are not null then do somethign differeent
					//conditoinal would have to be above the above line
					//but it conflicts with the above if condition
			}
			else if(temp->Target->right != nullptr && temp->Target->left == nullptr) {
				root = temp->Target->right;
				//temp->Target->right = nullptr;
				//below line is unnecessary but it does help in some corner cases
				//temp->Target->right->left = temp->left //THIS ONLY WORKS IF target has no children
					//TO DO
					//could put conditionals where if temp->left and temp->Target->right->left are not null then do somethign differeent
					//conditional would have to be above the above line
					//but it conflicts with the above else if condition
			}
			else if (temp->Target->right != nullptr && temp->Target->left != nullptr) {
				//TO DO
				//handle cases where there are collisions.
				//how to handle the branch that has no easy way to be reinserted into the tree
				//find minimum in right subtree
				//copy the value in targeted node
				//remove the minimum in right subtree
				//****************WHHHHHOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOPPPPPPPPPSS
				//I DID THIS AS IF IT WERENT ROOT, BUT IT IS ROOT
				//MAYBE IT WORKS ANY WAY BUT DOUBLE CHECK
				//seems to be valid so thumbs up
				if (temp->Target->right->left == nullptr) {
					temp->Target->data = temp->Target->right->data;
					Node<T>* temp2 = temp->Target->right;
					temp->Target->right = temp->Target->right->right;
					delete temp2;
					exception = true;
				}
				else {
					Node<T>* minimum = FindMin(temp->Target->right,temp->Target->right->left);
					if (minimum->left != nullptr && minimum->left->right != nullptr) {
						temp->Target->data = minimum->left->data;
						Node<T>* temp3 = minimum->left;
						minimum->left = minimum->left->right;
						delete temp3;

					}
					else {
						temp->Target->data = minimum->left->data;  
						delete minimum->left;
						minimum->left = nullptr;
						//delete minimum;
						exception = true;

						//TODO
						//I THINK THIS HANDLES ALL CASES EXCEPT WHEN the minimum has a right child

						//THIS TO DO SHOULD BE ABOVE INBETWEEN ELSE AND LINE BELOW MINIMUM

						//THIS IS WHERE YAH DO RECURSION

					}





				}





				}

			if (!exception) {
				delete temp;
			}
			temp->Target_Parent = nullptr;
			temp->isTarget = false;
			temp->Target = nullptr;
		}

	}
	else {
		//remove
		if (temp->Target!= nullptr && (temp->Target->left !=nullptr || temp->Target->right !=nullptr)) {//children
			//have to reinsert children in tree
			// //rebalance
			//TODO


			if (temp->Target->left != nullptr && temp->Target->right == nullptr) {
				
				//this should mirror the above
				//except instead of dealing with root
				//deal with temp->Target_Parent
				//so copy code and repla
				if (temp->Target_Parent->left == temp->Target) {
					temp->Target_Parent->left = temp->Target->left;
				}
				else if (temp->Target_Parent->right == temp->Target) {
					temp->Target_Parent->right = temp->Target->left;
				}
				else {
					//error
				}
				//Target_Parent = temp->Target->left;
				//temp->Target->left = nullptr;
				//below line is unnecessary
				//temp->Target->left->right = temp->right



			}
			else if(temp->Target->right != nullptr && temp->Target->left == nullptr){
				if (temp->Target_Parent->left == temp->Target) {
					temp->Target_Parent->left = temp->Target->right;
				}
				else if (temp->Target_Parent->right == temp->Target) {
					temp->Target_Parent->right = temp->Target->right; //Target parent points to a parent
					//but it doesnt point from left or right
					//never change target_parent
				}
				//temp->Target->right = nullptr;
				//below line is unnecessary but it does help in some corner cases
				//temp->Target->right->left = temp->left //THIS ONLY WORKS IF target has no children



			}
			else if (temp->Target->right != nullptr && temp->Target->left != nullptr) {

				//TODO



				//find minimum in right subtree
				//copy the value in targeted node
				//remove the minimum in right subtree
				//******************* THIS IS THE SAME CODE AS ABOVE but it was done as if it werent root
				//this should ***************** work , btu above code might not work
				if (temp->Target->right->left == nullptr) {
					//this checks to see if the conditions are right for the 
					//recursion to end in one loop
					//if it doesnt then the else catches everything else
					temp->Target->data = temp->Target->right->data;
					//temp->Target->value = minimum->value;
					Node<T>* temp2 = temp->Target->right;
					temp->Target->right = temp->Target->right->right;
					//do i need to set the pointers to null??
					delete temp2;
					exception = true;
				}
				else {
					Node<T>* minimum = FindMin(temp->Target->right, temp->Target->right->left);
					if (minimum->left != nullptr && minimum->left->right != nullptr) {
						temp->Target->data = minimum->left->data;
						Node<T>* temp3 = minimum->left;
						minimum->left = minimum->left->right;
						delete temp3;

					}
					else {
						temp->Target->data = minimum->left->data;  //should this dereference?
						//* in front to derefernce?????????  im not sure
						//temp->Target->value = minimum->value;
						// uncomment value if add value to node
						delete minimum->left;
						minimum->left = nullptr;
						//delete minimum;
						exception = true;

						//TODO
						//I THINK THIS HANDLES ALL CASES EXCEPT WHEN the minimum has a right child

						//THIS TO DO SHOULD BE ABOVE INBETWEEN ELSE AND LINE BELOW MINIMUM

						//THIS IS WHERE YAH DO RECURSION


					}


				}



			}
			/*
			else {
				//no children under target, so simply change parents pointer to it to null and delete
			if(temp->Target_Parent->left==temp->Target)
				temp->Target_Parent->left = nullptr;
			else if (temp->Target_Parent->right == temp->Target)
				temp->Target_Parent->right = nullptr;
			else {
				//error
			}
			}
			*/



			
			temp->Target_Parent = nullptr;
			temp->isTarget = false;
			temp->Target = nullptr;
			delete temp;

		}
		else {//nochildren
			//isleaf
			if (temp->Target_Parent != nullptr && temp->Target != nullptr) {


				if (temp->Target_Parent->left == temp->Target) {
					temp->Target_Parent->left = nullptr;
				}
				else {
					temp->Target_Parent->right = nullptr;
				}

				temp->isTarget = false;
				temp->Target_Parent == nullptr;
				temp->Target == nullptr;
				delete temp;


			}

		}
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
Node<T>* BinarySearchTree<T>::FindMinimum(Node<T>* start, Node<T>* target) {
	//recurssion
	if (start->left==nullptr) {
		return start;  //only problem is you wont know if it stops at if it stops at the start
		//have to check that when ever u call this function
		//THIS IS BAD IF THIS HAPPENS FIRSTIME
	}
	else if (start->left->left == nullptr) {
		return start;
	}
	else {
		return FindMinimum(start->left, start->left->left);
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

	if (parent == nullptr && child == nullptr) {
		//this basically says we are at the root, parent and child of the current search position don't necessarily
		//equal null, 
		//but once we check if the parent and or child of the value supplied by grandparent is nullptr
		//then there are no more children to check
		if (grandparent == nullptr) {
			return nullptr; //not found
		}
		else if (*grandparent->key == inval) {
			grandparent->isTarget = true;
			grandparent->Target_Parent = nullptr;  //***************************************** even if u put root it wont work, will have to deal with the root issue iftarget is true, then change what root points too manually ********************
			grandparent->Target = grandparent; 
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
			grandparent->isTarget = false;
			grandparent->Target_Parent = grandparent;  //***************************************** even if u put root it wont work, will have to deal with the root issue iftarget is true, then change what root points too manually ********************
			grandparent->Target = parent;
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
			grandparent->isTarget = false;  //***************************************** even if u put root it wont work, will have to deal with the root issue iftarget is true, then change what root points too manually ********************
			grandparent->Target_Parent = parent; 
			grandparent->Target = child;
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
	if (toprint == NULL) return;
	cout << *toprint->key << " ( ";
	if (toprint->left != nullptr) {
		cout << *toprint->left->key;
	}
	cout << " ,";
	if(toprint->right!=nullptr)
		cout << *toprint->right->key;
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
	if (L == 0 && R == 0)//(L==nullptr && R==nullptr)
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
	bool children = false;
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











template <typename T>
Node<T>* BinarySearchTree<T>::DEADFUNCTION(T* inval, Node<T>* parent) {
	/////////////////////////////  DONT USE CODE BELOW
	/////////////////////////////////////////////////////////////////////////////
	Node<T>* tempgrandchild = FindTransverse(inval, root);
	Node<T>* temp = FindTransverseFamily(inval, root, nullptr, nullptr);
	bool children = false;

	if (tempgrandchild == nullptr) {
		return; //nothing to remove   SHould PRINT OUT A THROW EXCEPTION BUT KEEP PROGRAM RUNNING
	}
	if (temp == nullptr) {
		return;  //nothing to remove   SHould PRINT OUT A THROW EXCEPTION BUT KEEP PROGRAM RUNNING
	}
	if (tempgrandchild->right != nullptr || tempgrandchild->left != nullptr) {
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
				root == nullptr;  //*************************************************************
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
				//else {
					//dont need this else
				//}
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
				//else {
					//dont need this else
			   // }
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