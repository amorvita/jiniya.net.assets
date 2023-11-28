#include "StdAfx.h" 
#include "mouse.h"

const CPosition CMouse::_dir[8] = {
	CPosition( 0,-1),
	CPosition( 1,-1),
	CPosition( 1, 0),
	CPosition( 1, 1),

	CPosition( 0, 1),
	CPosition(-1, 1),
	CPosition(-1, 0),
	CPosition(-1, 1)
};

/*
void CMouse::_dir_init() {
	_dir[0].set_xy(0,-1);
	_dir[1].set_xy(1,-1);
	_dir[2].set_xy(1,0);
	_dir[3].set_xy(1,1);

	_dir[4].set_xy(0,1);
	_dir[5].set_xy(-1,1);
	_dir[6].set_xy(-1,0);
	_dir[7].set_xy(-1,1);
}
*/

CMouse::CMouse() {
	_curpos.set_xy(0, 0);
	_curdir = 0;

//	_dir_init();
}

CMouse::CMouse(CPosition &pos) {
// ASSERT;
	_curpos = pos;
	_curdir = 0;

//	_dir_init();
}

CPosition CMouse::get_curpos() {
	CPosition temp(_curpos);

	return temp;
}

int CMouse::get_dir() {
	return _curdir;
}

void CMouse::set_dir(int d) {
	_curdir = d;
}

void CMouse::move_direction(int dir) {
//	ASSERT(dir < 0 || dir > 7);

	_curpos = _curpos + _dir[dir];
}

CPosition CMouse::next_position(int dir) {
//	ASSERT(dir < 0 || dir > 7);

	CPosition temp;

	temp = _curpos + _dir[dir];
	return temp;
}

void CMouse::set_pos(CPosition &pos) {
	_curpos = pos;
}

void CMouse::set_pos(int x, int y) {
	_curpos.set_xy(x, y);
}

//#define MOUSE_MODULE_TEST
#ifdef MOUSE_MODULE_TEST

#include <iostream.h>

void main() {
	CMouse m;
	CPosition t;

	t = m.get_curpos();

	cout << t.get_x() << t.get_y() << endl;

	t = m.next_position(2);

	cout << t.get_x() << t.get_y() << endl;

	m.move_direction(2);
	t = m.get_curpos();
	cout << t.get_x() << t.get_y() << endl;

	t = m.next_position(3);

	cout << t.get_x() << t.get_y() << endl;

}

#endif