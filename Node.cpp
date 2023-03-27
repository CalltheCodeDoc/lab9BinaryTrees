#include "Node.h"

template <typename T>
Node<T>::Node(T inval) {
	data = inval; //i think
	//or is data the count????
	left = nullptr;
	right = nullptr;
	//DO we let Node handle connections to other nodes or BinarySearchTree?
}

template <typename T>
Node<T>::~Node() {
	delete left;
	delete right;
	//maybe delete value
}