#ifndef MAZE_H
#define MAZE_H

#include "mouse.h"
#include "stack.h"

typedef struct Items Items;

class CMaze {
	private:
		enum {EMPTY = 0};
		int *_maze;
		CMouse _mice;
		CStack<CMouse> stk;
		CLinklist<CMouse> lst;
		int _maxx, _maxy;
		int _total_visit, _back_track;

	public:
		CMaze(int maxx = 12, int maxy = 12);
		~CMaze();

//		int is_valid(int x, int y);
		int is_empty(int x, int y);
		int is_empty(CPosition &pos);
		int resize_maze(int maxx = 12, int maxy = 12);
		int find_solution();
};

#endif