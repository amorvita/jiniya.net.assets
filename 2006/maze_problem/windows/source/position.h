#ifndef POSITION_H
#define POSITION_H

#include "StdAfx.h"

class CPosition {
	private:
		int _x, _y;

	public:
		CPosition(int x=0, int y=0);

		void set_xy(int x, int y);
		void set_y(int y);
		void set_x(int x);
		int get_x();
		int get_y();

	public:
		CPosition operator+(const CPosition &rhs);
};

#endif
