#pragma once
#include<iostream>
#include"QNode.h";

using namespace std;

template<typename T>
class Queue
{
    QNode<T>* front;
    QNode<T>* rear;
    int count;
public:
    Queue() {
        front = rear = nullptr;
        count = 0;
    }

    bool isempty()
    {
        if (front == NULL && rear == NULL)
            return true;
        else
            return false;
    }

    //function to enter elements in queue
    void enqueue(T item)
    {
        QNode<T>* newNode = new QNode<T>;
        newNode->setItem(item);
        newNode->setNext(nullptr);

        //If inserting the first element/node
        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
        }
        count++;
    }

    //function to delete/remove element from queue
    T dequeue()
    {
        if (isempty())
            return nullptr;
        else {
            count--;
            //only one element/node in queue.
            if (front == rear)
            {
                T temp = front->getItem();
                //delete front;
                front = rear = NULL;
                return temp;
            }
            else
            {
                T currPtr = front->getItem();
                front = front->getNext();
                //delete dltPtr;
                return currPtr;
            }
        }
    }

    //function to show the element at front
    T peek()
    {
        if (isempty())
            return nullptr;
            //cout << "Queue is empty\n";
        else
            return front->getItem();
            //cout << "element at front is:" << front->getItem();

        
    }

    //function to display queue
    void print()
    {
        if (isempty())
            return;
        else
        {
            QNode<T>* traverser = front;
            while (traverser != NULL)
            {
                cout << traverser->getItem();
                if(traverser->getNext())
                    cout << ",";
                traverser = traverser->getNext();
            }
        }
    }

    int getCount() const {
        return count;
    }
};

