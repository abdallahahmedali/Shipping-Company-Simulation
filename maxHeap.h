#pragma once
#include<iostream>
#include "Node.h"
using namespace std;

template<typename T>
class maxHeap {
	Node<T>** harr; // Pointer To The Array In Which The Heap Data Is Stored
	int capacity; // Maximum Size
	int heap_size; // Current Size
public:
	maxHeap(int cap) {
		heap_size = 0;
		capacity = cap;
		harr = new Node<T>*[cap];
		for (int i = 0; i < capacity; i++)
		{
			harr[i] = nullptr;
		}
	}
	~maxHeap() {
		delete[] harr;
	}
	int getSize() {
		return heap_size;
	}
	int getParent(int i) {
		return (i - 1) / 2;
	}
	int getLeft(int i) {
		return 2 * i + 1;
	}
	int getRight(int i) {
		return 2 * i + 2;
	}
	Node<T>* getMax() { // Returns Root Node Only
		return harr[0];
	}
	Node<T>* extractMax() { // Returns & Removes The Root Node
		if (heap_size <= 0) {
			return nullptr;
		}
		if (heap_size == 1)
		{
			heap_size--;
			return harr[0];
		}
		Node<T>* root = harr[0];
		harr[0] = harr[heap_size - 1];
		heap_size--;
		maxHeapify(0);
		return root;
	}
	void insertNode(Node<T>* newNode) { // Insert New Node
		if (heap_size == capacity) {
			cout << "Error : Your Heap Is Full !" << endl;
			return;
		}
		heap_size++;
		int i = heap_size - 1;
		harr[i] = newNode;
		while (i != 0 && *harr[getParent(i)] < *harr[i]) {
			swap(harr[i], harr[getParent(i)]);
			i = getParent(i);
		}
	}
	void maxHeapify(int i) { // Restructures The Heap After Extraction Process
		int l = getLeft(i);
		int r = getRight(i);
		int largest = i;
		if (l < heap_size && *harr[l] > *harr[i])
			largest = l;
		if (r < heap_size && *harr[r] > *harr[largest])
			largest = r;
		if (largest != i)
		{
			swap(harr[i], harr[largest]);
			maxHeapify(largest);
		}
	}
	void printArr() {
		for (int i = 0; i < heap_size; i++) {
			cout << harr[i]->getItem();
			if (i != heap_size - 1)
				cout << ",";
		}
		//cout << endl;
	}

};