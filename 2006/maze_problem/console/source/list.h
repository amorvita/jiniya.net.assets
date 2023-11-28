#include <iostream>
#include <fstream>
#include <string>

#ifndef LIST_H
#define LIST_H

#include "my_assert.h"

template <class T> class CLinklist;

template <class T>
class CLink {
	private:
		T _data;
		CLink<T> *_next;
		CLink<T> *_prev;

	public:
		friend class CLinklist<T>;
};

template <class T>
class CLinklist {
	protected:
		CLink<T> *_head, *_tail;
		int _size;
		
	public:
		CLinklist();
		~CLinklist();
		
		CLink<T> *get_head();
		CLink<T> *get_tail();
		CLink<T> *get_next(CLink<T> *temp);
		CLink<T> *get_prev(CLink<T> *temp);

		int addtail(T& data);
		void deltail();
		int addhead(T& data);
		void delhead();

		int ins_next(CLink<T> *node, T& data);
		int ins_prev(CLink<T> *node, T& data);
		void del_node(CLink<T> *node);

	//	blist& operator[](int&);
		T &get_node(CLink<T> *node);
		T &get_at(int n);

		int get_size();
};

template <class T>
CLinklist<T> :: CLinklist() {
	_head = NULL;
	_tail = NULL;
	_size = 0;
}

template <class T>
CLinklist<T> :: ~CLinklist() {
	CLink<T> *temp = _head;

	while(temp != NULL) {
		_head = _head->_next;
		delete temp;
		temp = _head;
	}
}

template <class T>
CLink<T> *CLinklist<T> :: get_head() {
	return _head;
}

template <class T>
CLink<T> *CLinklist<T> :: get_tail() {
	return _tail;
}

template <class T>
CLink<T> *CLinklist<T> :: get_next(CLink<T> *temp) {
	return temp->_next;
}

template <class T>
CLink<T> *CLinklist<T> :: get_prev(CLink<T> *temp) {
	return temp->_prev;
}

template <class T>
int CLinklist<T> :: addtail(T& data) {
	CLink<T>* newlink = new CLink<T>;
	if(newlink == NULL)
		return -1;

	newlink->_data = data;

	if(_head == NULL) {
		_head = _tail = newlink;
		_head->_prev = NULL;
		_tail->_next = NULL;
	} else {
		_tail->_next = newlink;
		newlink->_prev = _tail;

		_tail = newlink;
		_tail->_next = NULL;
	}
	++_size;
	return _size;
}

template <class T>
void CLinklist<T> :: deltail() {
	ASSERT(_size > 0 && _tail != NULL);

	CLink<T> *temp = _tail;

	if(_tail->_prev != NULL) {
		_tail = _tail->_prev;
		_tail->_next = NULL;
	} else
		_head = _tail = NULL;

	--_size;
	delete temp;
}

template <class T>
int CLinklist<T> :: addhead(T& data) {
	CLink<T>* newlink = new CLink<T>;
	if(newlink == NULL)
		return -1;

	newlink->_data = data;

	if(_head == NULL) {
		_head = _tail = newlink;
		_head->_prev = NULL;
		_tail->_next = NULL;
	} else {
		_head->_prev = newlink;
		newlink->_next = _head;

		_head = newlink;
		_head->_prev = NULL;
	}
	++_size;
	return _size;
}

template <class T>
void CLinklist<T> :: delhead() {
	CLink<T> *temp = _head;

	if(_head->_next != NULL) {
		_head = _head->_next;
		_head->_prev = NULL;
	} else
		_head = _tail = NULL;

	delete temp;
	--_size;
}

template <class T>
int CLinklist<T> :: ins_next(CLink<T> *node, T& data) {
	ASSERT(node != NULL && _size > 0);
	CLink<T>* newlink = new CLink<T>;
	if(newlinke == NULL)
		return -1;

	newlink->_data = data;

	newlink->prev = node;
	newlink->next = node->next;

	if(node->next != NULL)
		node->next->prev = newlink;

	node->next = newlink;

	_size++;
	return _size;
}

template <class T>
int CLinklist<T> :: ins_prev(CLink<T> *node, T& data) {
	ASSERT(node != NULL && _size > 0);
	CLink<T>* newlink = new CLink<T>;
	if(newlinke == NULL)
		return -1;

	newlink->_data = data;

	newlink->prev = node->prev;
	newlink->next = node;

	if(node->prev != NULL)
		node->prev->next = newlink;

	node->prev = newlink;

	_size++;
	return _size;
}

template <class T>
void CLinklist<T> :: del_node(CLink<T> *node) {
	ASSERT(node != NULL && _size > 0);

	if(node->prev != NULL)
		node->prev->next = node->next;

	if(node->next != NULL)
		node->next->prev = node->prev;

	delete node;
}

template <class T>
T &CLinklist<T> :: get_node(CLink<T> *node) {
	ASSERT(node != NULL && _size > 0);

	return node->_data;
}

template <class T>
T &CLinklist<T> :: get_at(int n) {
	ASSERT(n >= 0 && n < _size);

	CLink<T> *current = _head;

	for(int i = 0; i< n; ++i)
		current = current->_next;

	return current->_data;
}

template <class T>
int CLinklist<T> :: get_size() {
	return _size;
}
#endif
