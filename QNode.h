#pragma once

template<typename T>
class QNode
{
private:
	T item;
	QNode<T>* next;
public:

	QNode()
	{
		next = nullptr;
	}

	QNode(T newItem)
	{
		item = newItem;
		next = nullptr;
	}

	void setItem(T newItem)
	{
		item = newItem;
	}

	void setNext(QNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem() const
	{
		return item;
	}

	QNode<T>* getNext() const
	{
		return next;
	}
};