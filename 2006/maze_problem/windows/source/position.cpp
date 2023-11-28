#include "StdAfx.h" 
#include "position.h"

CPosition::CPosition(int x, int y) {
	_x = x;
	_y = y;
}

void CPosition::set_x(int x) {
	_x = x;
}

void CPosition::set_y(int y) {
	_y = y;
}

void CPosition::set_xy(int x, int y) {
	_x = x;
	_y = y;
}

int CPosition::get_x() {
	return _x;
}

int CPosition::get_y() {
	return _y;
}

CPosition CPosition::operator+(const CPosition &rhs) {
	return CPosition(_x + rhs._x, _y + rhs._y);
}

//#define POSITION_MODULE_TEST
/*
#ifdef POSITION_MODULE_TEST

#include <iostream.h>

void main() {
	Position p, q, r;

	p.set_xy(3, 4);
	q.set_xy(2, 2);

	r = p + q;

	cout << r.get_x() << r.get_y() << endl;
	
}

#endif
*/