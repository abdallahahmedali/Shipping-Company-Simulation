#pragma once
#include<iostream>
#include"QNode.h";
using namespace std;
template<typename T>
class linkedList {
	QNode<T>* head;
	int count;
public:
	linkedList() {
		head = NULL;
		count = 0;
	}
	
	int getCount() const{
		return count;
	}

	void insert_beg(T item) {

		//--------- Inserting At The start Of The List -------------//
		QNode<T>* newNode = new QNode<T>;
		newNode->setItem(item);
		newNode->setNext(nullptr);
		QNode<T>* traverser = head;
		if (head == nullptr)
		{
			head = newNode;
		}
		else {
			newNode->setNext(head);
			head = newNode;
		}
		count++;
	}

	

	void insert(T item) {

		//--------- Inserting At The End Of The List -------------//
		QNode<T>* newNode = new QNode<T>;
		newNode->setItem(item);
		newNode->setNext(nullptr);
		QNode<T>* traverser = head;
		if (head == nullptr)
		{
			head = newNode;
		}
		else {
			while (traverser->getNext()) {
				traverser = traverser->getNext();
			}
			traverser->setNext(newNode);
		}
		count++;
	}
	
	template<typename T2>
	T getPtrTo(T2 target) {
		QNode<T>* traverser = head;
		while (traverser) {
			if (*(traverser->getItem()) == target)
				return traverser->getItem();
			traverser = traverser->getNext();
		}
		if (traverser)
			return traverser->getItem();
		else
			return nullptr;
	}
	

	template<typename T2>
	bool contains(T2 data) {
		return getPtrTo(data) != nullptr;
	}

	T remove(T data) {
		QNode<T>* tempNode = nullptr;

		QNode<T>* traverser = head;
		if (head->getItem() == data)
		{
			tempNode = head;
			head = head->getNext();
			count--;
			return tempNode->getItem();
		}
		while (traverser && traverser->getNext()) {

			if (traverser->getNext()->getItem() == data)
			{
				tempNode = traverser->getNext();
				traverser->setNext(traverser->getNext()->getNext());
				count--;
				return tempNode->getItem();
			}

			traverser = traverser->getNext();
		}

		return nullptr;


	}
	// dequeue Function
	T remove() {
		if (!head)
			return nullptr;
		else {
			count--;
			QNode<T>* temp = head;
			head = head->getNext();
			return temp->getItem();
		}
	}

	void clear() {
		QNode<T>* traverser = head;
		while (traverser != NULL)
		{
			head = head->getNext();
			delete traverser;
			traverser = head;
		}
		count = 0;
	}

	bool isEmpty() {
		return head == nullptr;
	}

	void print() {
		QNode<T>* traverser = head;

		while (traverser != NULL) {
			cout << traverser->getItem();
			if (traverser->getNext())
				cout << ",";
			traverser = traverser->getNext();
		}
	}
	T peek()
	{ if(head)
		 return head->getItem();
	 else return nullptr;
	}

	~linkedList() {
		clear();
	}
};
