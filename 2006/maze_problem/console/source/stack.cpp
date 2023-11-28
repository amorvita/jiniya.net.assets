#include <iostream>
#include "stack.h"
#include "queen.h"

Stack :: Stack() {
	top = -1;
}

void Stack :: init() {
	top = -1;
}

QUEEN Stack :: pop() {
	if(!is_empty())
		return lst.get_at(top--);
}

int Stack :: push(QUEEN& t) {
	lst.additem(t);
	top++;
	return TRUE;
}

int Stack :: is_empty() {
	return (top == -1) ? TRUE : FALSE;
}

Stack& Stack :: operator>>(QUEEN& t) {
	t = pop();
	return *this;
}

Stack& Stack :: operator<<(QUEEN& t) {
	push(t);
	return *this;
}

/*
int main() {
	Stack stk;
//	linklist<QUEEN> lst;
	QUEEN a(3,4), b(2,3), c(1,0);

	stk << a << b << c;

	stk >> c >> b >> a;

	cout << c.get_x() ;
	return 0;
}
*/
