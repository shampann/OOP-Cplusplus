#pragma once

/*
	If some memory allocations failed- throws exeption.
	If the peek() or dequeue() is called with empty tail- throws exeption.
*/

#include "Elem.h"

template <class T>
class Tail
{
public:
	Tail();
	Tail(const Tail<T>& other);
	Tail<T>& operator=(const Tail<T>& other);
	~Tail();
public:
	T peek() const;
	T dequeue();
	void enqueue(const T& el);
	bool isEmpty() const;
	size_t getSize() const;
private:
	void copyFrom(const Tail<T>& other);
	void free();
	void init();
private:
	Elem<T> *head, *tail;
	size_t size;
};

template <class T>
Tail<T>::Tail()
{
	init();
}

template <class T>
Tail<T>::Tail(const Tail<T>& other)
{
	copyFrom(other);
}

template <class T>
Tail<T>& Tail<T>::operator=(const Tail<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
Tail<T>::~Tail()
{
	delete tail;
}

// returns a copy of the value of the next item in the tail.

template <class T>
T Tail<T>::peek() const
{
	if (isEmpty())
		throw "The tail is empty and called peek()!";

	return tail->data;
}

template <class T>
T Tail<T>::dequeue()
{
	if (isEmpty())
		throw "The tail is empty and called dequeue()!";

	Elem<T> * x = tail;
	tail = tail->next;	// if the element was last one, the next will be NULL, so the tail will be NULL->empty tail
	T val = x->data;
	x->next = NULL;		// to break the cascade destructor of the Elem class
	delete x;
	--size;
	return val;
}

template <class T>
void Tail<T>::enqueue(const T& other)
{
	Elem<T> * p = new Elem<T>(other); // creates new cell with value- 'other' and next pointer- 'NULL'
	
	// if the list is empty- makes the tail and the head pointing the created element
	if (isEmpty())
		tail = p;
	else
		head->next = p;

	head = p;
	++size;
}

template <class T>
bool Tail<T>::isEmpty() const
{
	return tail == NULL; // size == 0
}

template <class T>
size_t Tail<T>::getSize() const
{
	return size;
}

template <class T>
void Tail<T>::copyFrom(const Tail<T>& other)
{
	if (!other.isEmpty())
	{
		// let`s set the tail pointer
		tail = new Elem<T>(*other.tail);

		// and now let`s set the head pointer
		// to set the head pointer it had to go thru all elements of the tail...
		Elem<T> * p = tail;
		while (p->next != NULL)
		{
			p = p->next;
		}

		head = p;

		size = other.size;
	}
	else
	{
		init();
	}
}

// the destructor of the Elem class is cascade, so he will delete the rest of the elements in the tail

template <class T>
void Tail<T>::free()
{
	delete tail; // If the tail is empty(tail == NULL), the delete won't do anything..
	init();
}

template <class T>
void Tail<T>::init()
{
	tail = head = NULL;
	size = 0;
}