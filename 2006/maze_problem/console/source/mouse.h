#ifndef MOUSE_H
#define MOUSH_H

#include "position.h"

class CMouse {
	private:
		CPosition _curpos;
		int _curdir;
		static const CPosition _dir[8];
		//const int dir[8];

	private:
		//void _dir_init();

	public:
		CMouse();
		CMouse(CPosition &pos);

		CPosition next_position(int dir);
		void move_direction(int dir);
		int get_dir();
		void set_dir(int d);
		CPosition get_curpos();
		void set_pos(CPosition &pos);
		void set_pos(int x, int y);
};

#endif