#ifndef STACK_H
#define STACK_H

#include "list.h"

template <class T>
class CStack {
	private:
		CLinklist<T> _data;

	public:
		int is_empty();
		int get_size();

		T &pop(T& temp);
		int push(T& data);
		CStack<T>& operator>>(T& temp);
		CStack<T>& operator<<(T& data);

		T &operator[](int n);
};

template <class T>
int CStack<T> :: is_empty() {
	if(_data.get_size() > 0)
		return false;
	else
		return true;
}

template <class T>
int CStack<T> :: get_size() {
	return _data.get_size();
}

template <class T>
T &CStack<T> :: pop(T& temp) {
	ASSERT(!is_empty());
	CLink<T> *d = _data.get_tail();

	temp = _data.get_node(d);
	_data.deltail();
	
	return temp;
}

template <class T>
int CStack<T> :: push(T& data) {
	return _data.addtail(data);
}

template <class T>
CStack<T> &CStack<T> :: operator>>(T& temp) {
	pop(temp);

	return *this;
}

template <class T>
CStack<T> &CStack<T> :: operator<<(T& data) {
	push(data);

	return *this;
}

template <class T>
T &CStack<T> :: operator[](int n) {
	return _data.get_at(n);
}

#endif
