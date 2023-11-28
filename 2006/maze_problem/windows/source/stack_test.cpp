#include <iostream.h>
#include "stack.h"

//#define STACK_MODULE_TEST
#ifdef STACK_MODULE_TEST

int main() {
	CStack<int> ba;
//	CLink<int> *temp;
	int a;

	a=3;
	ba.push(a);
	a=5;
	ba.push(a);
	a=6;
	ba.push(a);
	a=7;
	ba.push(a);

	a=3;
	ba << a;

	a=5;
	cout << ba[0] << endl;
	cout << ba[1] << endl;
	cout << ba[2] << endl;
	cout <<	ba.pop(a) << endl;
	cout <<	ba.pop(a) << endl;
	cout << ba.get_size() << endl;

	return 0;
}

#endif