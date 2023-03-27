#pragma once
#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {

public:
	Node(T inval);
	~Node();
	T data; //value
	T key;
	Node* left;
	Node* right;
};
#endif