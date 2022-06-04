#pragma once
#include<iostream>
#include "maxHeap.h"
using namespace std;

template<typename T>
class priorityQueue {
	maxHeap<T>* myQueue;
public:
	priorityQueue(int cap) {
		myQueue = new maxHeap<T>(cap);
	}
	~priorityQueue() {
		delete myQueue;
	};
	void enqueue(T item, float priority) {
		Node<T>* newNode = getNewNode(item, priority);
		myQueue->insertNode(newNode);
	}

	void enqueue(Node<T>* node) {
		myQueue->insertNode(node);
	}

	T dequeue() {
		Node<T>* node = myQueue->extractMax();
		if (!node) {
			//cout << "Error : Can't Dequeue , The Queue Is Already Empty !" << endl;
			return nullptr;
		}
		else
			return node->getItem();
	}

	T peek() {
		Node<T>* node = myQueue->getMax();
		if (!node || myQueue->getSize() == 0) {
			//cout << "Error : Can't Dequeue , The Queue Is Already Empty !" << endl;
			return nullptr;
		}
		else
			return node->getItem();
	}

	int getCount() {
		return myQueue->getSize();
	}

	void print() {
		myQueue->printArr();
	}
};
