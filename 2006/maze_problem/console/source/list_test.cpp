#include <iostream.h>
#include "list.h"

//#define LIST_MODULE_TEST
#ifdef LIST_MODULE_TEST

int main() {
	CLinklist<int> ba;
	CLink<int> *temp;
	int a;

	a=3;
	ba.addtail(a);
	a=4;
	ba.addtail(a);
	a=5;
	ba.addtail(a);

	a=2;
	ba.addhead(a);
	a=4;
	ba.addtail(a);
	a=7;
	ba.addhead(a);

	temp = ba.get_head();
	while(temp != NULL) {
		cout << ba.get_node(temp) << endl;
		temp = ba.get_next(temp);
	}

	ba.deltail();

	return 0;
}

#endif