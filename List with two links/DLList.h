#pragma once

#include "Elem.h"


template <class T>
class DLList
{
public:
	DLList();
	DLList(const DLList<T>& other);
	DLList<T>& operator=(const DLList<T>& other);
	~DLList();
public:
	T peek_front() const;
	T peek_back() const;
	T pop_front();
	T pop_back();
	void push_front(const T& x);
	void push_back(const T& x);
	bool isEmpty() const;
private:
	void init();
	void free();
	void copyFrom(const DLList<T>& other);
private:
	Elem<T> * head;

public:
	class Iterator
	{
		friend class DLList<T>;
	public:
		Iterator(Elem<T>* pElement, DLList<T>* pOwner);
		operator bool() const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		T& operator*();
		const T& operator*() const;
		typename DLList<T>::Iterator& operator++();
		typename const DLList<T>::Iterator& operator++() const;
	private:
		DLList<T>* owner;
		Elem<T>* element;
	};
public:
	Iterator begin();
	Iterator end();
	void removeAt(Iterator& iter);
};

template <class T>
DLList<T>::DLList()
{
	init();
}

template <class T>
DLList<T>::DLList(const DLList<T>& other)
{
	copyFrom(other);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
DLList<T>::~DLList()
{
	free();
}

template <class T>
T DLList<T>::peek_front() const
{
	if (isEmpty())
		throw "The list is empty and called peek_front()!";
	
	return head->next->data;
}

template <class T>
T DLList<T>::peek_back() const
{
	if (isEmpty())
		throw "The list is empty and called peek_back()!";

	return head->prev->data;
}

template <class T>
T DLList<T>::pop_front()
{
	if (isEmpty())
		throw "The list is empty and called pop_front()!";

	Elem<T>* n = head->next;

	n->next->prev = head;
	head->next = n->next;

	n->prev = n->next = NULL;
	T val = n->data;
	delete n;
	return val;
}

template <class T>
T DLList<T>::pop_back()
{
	if (isEmpty())
		throw "The list is empty and called pop_back()!";

	Elem<T>* n = head->prev;

	n->prev->next = head;
	head->prev = n->prev;

	n->next = n->prev = NULL;
	T val = n->data;
	delete n;
	return val;
}

template <class T>
void DLList<T>::push_front(const T& x)
{
	Elem<T> * newElem = new Elem<T>(x);
	newElem->next = head->next;
	newElem->prev = head;

	if (!isEmpty()) 
	{
		head->next->prev = newElem;
	}
	else
	{
		head->prev = newElem;
	}

	head->next = newElem;
}

template <class T>
void DLList<T>::push_back(const T& x)
{
	Elem<T> * newElem = new Elem<T>(x);
	newElem->next = head;
	newElem->prev = head->prev;

	if (!isEmpty())
	{
		head->prev->next = newElem;
	}
	else
	{
		head->next = newElem;
	}

	head->prev = newElem;
}

template <class T>
bool DLList<T>::isEmpty() const
{
	return head->next == head;
}

template <class T>
typename DLList<T>::Iterator DLList<T>::begin()
{
	return Iterator(head->next, this);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::end()
{
	return Iterator(head->prev, this);
}

template <class T>
void DLList<T>::removeAt(Iterator& iter)
{
	if (iter) // iter doesn`t points to the head
	{
		Elem<T> * n = iter.element;
		++iter;

		n->prev->next = n->next;
		n->next->prev = n->prev;

		n->next = n->prev = NULL;
		delete n;
	}
}

template <class T>
void DLList<T>::init()
{
	head = new Elem<T>();
	head->next = head;
	head->prev = head;
}

// It will delete the memory for the head cell and calls it`s cascade destructor.
// Does not reset the data after it! (doesn`t call init function)

template <class T>
void DLList<T>::free()
{
	Elem<T> * n = head->next;
	head->next = NULL;
	delete n;  // with the next pointer it will start from the first element and go thru all and delete the head element (head->next is null where it will stop)
}


template <class T>
void DLList<T>::copyFrom(const DLList<T>& other)
{
	init();

	Elem<T>* n = other.head;

	while (n->next != other.head)
	{
		push_back(n->next->data);
		n = n->next;
	}
}


/*

///
///	class Iterator
///

*/

template <class T>
DLList<T>::Iterator::Iterator(Elem<T>* pElement, DLList<T>* pOwner) : element(pElement), owner(pOwner) {}

template <class T>
DLList<T>::Iterator::operator bool() const
{
	return element != owner->head;
}

template <class T>
bool DLList<T>::Iterator::operator==(const Iterator& other) const
{
	return element == other.element;
}

template <class T>
bool DLList<T>::Iterator::operator!=(const Iterator& other) const
{
	return !operator==(other);
}

template <class T>
T& DLList<T>::Iterator::operator*()
{
	if (element == owner->head)
		throw "Invalid possition for the DLList iterator and called operator*()!";

	return element->data;
}

template <class T>
const T& DLList<T>::Iterator::operator*() const
{
	if (element == owner->head)
		throw "Invalid possition for the DLList iterator and called operator*()!";

	return element->data;
}

template <class  T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator++()
{
	element = element->next;
	return *this;
}

template <class  T>
typename const DLList<T>::Iterator& DLList<T>::Iterator::operator++() const
{
	element = element->next;
	return *this;
}