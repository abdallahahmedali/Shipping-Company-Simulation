#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Node
{
private:
	T item;
	float priority;
public:

	Node()
	{
		priority = 0;
	}

	Node(T newItem, float newPriority = 0)
	{
		item = newItem;
		priority = newPriority;

	}

	void setItem(T newItem)
	{
		item = newItem;
	}

	void setPriority(float newPriority)
	{
		priority = newPriority;
	}


	T getItem() const
	{
		return item;
	}

	float getPriority() const
	{
		return priority;
	}

	bool operator < (const Node<T>& node) {
		if (this->getPriority() < node.getPriority())
			return true;
		else
			return false;
	}

	bool operator > (const Node<T>& node) {
		if (this->getPriority() > node.getPriority())
			return true;
		else
			return false;
	}

};

template<typename T>
Node<T>* getNewNode(const T& item, const float& priority) {
	Node<T>* newNode = new Node<T>;
	newNode->setItem(item);
	newNode->setPriority(priority);
	return newNode;
}

template<typename T>
void swap(Node<T>* x, Node<T>* y) { // Swaps Two Elements In The Array
	T item = x->getItem();
	float priority = x->getPriority();
	x->setItem(y->getItem());
	x->setPriority(y->getPriority());
	y->setItem(item);
	y->setPriority(priority);
}

template <typename T>
ostream& operator << (ostream& out, Node<T>* node)
{
	if (node != nullptr)
		out << "(" << node->getItem() << ", " << node->getPriority() << ")";
	else
		cout << "";
	return out;
}
