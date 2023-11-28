#include "StdAfx.h" 
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cmaze.h"
#include "my_assert.h"

CMaze::CMaze(int maxx, int maxy, int seed) {
	_maze = NULL;
	resize_maze(maxx, maxy, seed);
}

CMaze::~CMaze() {
	if(_maze != NULL)
		delete [] _maze;

	_maze = NULL;
}

int CMaze::is_empty(int x, int y) {
	mASSERT(x >= 0 && x < _maxx);
	mASSERT(y >= 0 && y < _maxy);
	
	if(_maze[(_maxx - 1) * y + x] == EMPTY)
		return true;
	
	return false;
}

int CMaze::is_empty(CPosition &pos) {
	int x,y;

	x = pos.get_x();
	y = pos.get_y();
	mASSERT(x >= 0 && x < _maxx);
	mASSERT(y >= 0 && y < _maxy);
	
	if(_maze[(_maxx - 1) * y + x] == EMPTY)
		return true;
	
	return false;
}


int CMaze::resize_maze(int maxx, int maxy, int seed) {
	mASSERT(maxx > 4 && maxy > 4);
	mASSERT(seed > 1 && seed < maxx && seed < maxy);

	CMouse cms;

    int i, j,k;

	if(_maze != NULL)
		delete [] _maze;

	_maze = new int[(maxx+2) * (maxy+2)];

	if(_maze == NULL) {
		_maxx = 0;
		_maxy = 0;

		return false;
	}

	_maxx = maxx+2;
	_maxy = maxy+2;

	for(i=1;i<_maxy;++i) {
		for(j=1;j<_maxx;++j)
			_maze[i * (_maxx-1) + j] = 0;
		}

	srand(time(NULL));

	for(i=1;i<_maxy-1;++i) {
		for(j=1;j<seed;++j) {
			while((k = (rand() % (_maxx-1))+1) == k + 1)
				NULL;
			
			_maze[i * (_maxx-1) + k] = 1;
		}
	}

	// 첫줄, 끝줄을 1로 셋팅, 아래처럼
	// 111111111111111111111111111111111111111111111111111111
	// 미로 내용
	// 111111111111111111111111111111111111111111111111111111
	for(i=0;i<_maxx;++i) {
		_maze[i] = 1;
		_maze[(_maxx-1) * (_maxy-1) + i] = 1;
	}

	// 2번째 줄부터 외곽 내용을 1롤 셋팅, 아래처럼
	//
	// 1내용1
	// 1내용1
	for(i=1;i<_maxy-1;++i) {
		_maze[(_maxx-1) * i] = 1;
		_maze[(_maxx-1) * i + _maxx -1] = 1;
	}

	_maze[(_maxx-1) * 1 + 1] = 0;
	_maze[(_maxy-2) * (_maxx-1) + _maxx - 2] = 0;

	for(i=0;i<_maxy;++i) {
		for(j=0;j<_maxx;++j)
			printf("%2d ", _maze[(_maxx-1) * i + j]);

		printf("\n");
	}

	while(!stk.is_empty())
		stk.pop(cms);

	lst.del_all();
	return true;
}

void CMaze :: draw_maze(CDC *t, CDC *w, CDC *b, int x, int y) {
	int i,j,mx,my;
	int px = int(x / (_maxx-2));
	int py = int(y / (_maxy-2));

	RECT r = {0,0,x,y};
	CBrush br(RGB(160,160,160));

	t->FillRect(&r, &br);
	for(i=1;i<_maxy-1;++i) {
		for(j=1;j<_maxx-1;++j) {
			x = (j-1) * px + px/2;
			y = (i-1) * py + px/2;

			if(_maze[(_maxx-1) * i + j] == 0)
				t->BitBlt(x,y,5,5,w,0,0,SRCCOPY);
			else
				t->BitBlt(x,y,5,5,b,0,0,SRCCOPY);
		}
	}

	CPen pen(PS_SOLID, 2, RGB(255,0,0)),pen2(PS_SOLID,1,RGB(0,0,0)), *old;

	old = t->SelectObject(&pen2);
	for(i=1;i<_maxy-1;++i)
		for(j=1;j<_maxx-2;++j) {
			if(_maze[(_maxx-1) * i + j] == 1 && _maze[(_maxx-1) * i + j+1] == 1) {
				x = (j-1) * px + px/2;
				y = (i-1) * py + px/2;

				t->MoveTo(x+2,y+2);
				t->LineTo(px+x+2, y+2);
			}
		}

	for(j=1;j<_maxx-1;++j)
		for(i=1;i<_maxy-2;++i) {
			if(_maze[(_maxx-1) * i + j] == 1 && _maze[(_maxx-1) * (i+1) + j] == 1) {
				x = (j-1) * px + px/2;
				y = (i-1) * py + px/2;

				t->MoveTo(x+2,y+2);
				t->LineTo(x+2, py+y+2);
			}
		}

	t->SelectObject(old);
	pen2.DeleteObject();

	old = t->SelectObject(&pen);
	for(i=0;i<stk.get_size()-1;++i) {
		mx = (stk[i].get_curpos().get_x()-1) * px + px/2;
		my = (stk[i].get_curpos().get_y()-1) * py + py/2;
		t->MoveTo(mx, my);

		mx = (stk[i+1].get_curpos().get_x()-1) * px + px/2;
		my = (stk[i+1].get_curpos().get_y()-1) * py + py/2;
		t->LineTo(mx, my);
	}

	t->SelectObject(old);
	pen.DeleteObject();
}

int CMaze :: find_solution() {
	int *mark;
	int d;
	CPosition n;
	CMouse cms;

	mark = new int[_maxx * _maxy];
	if(mark == NULL)
		return -1;

	for(int i=1;i<_maxy-1;++i)
		for(int j=1;j<_maxx-1;++j)
			mark[i * (_maxx-1) + j] = 0;

	while(!stk.is_empty())
		stk.pop(cms);

	lst.del_all();

	mark[(_maxx-1)*1 + 1] = 1;

	_total_visit = _back_track = 0;
	_mice.set_pos(1,1);
	_mice.set_dir(2);
	stk << _mice;
	lst.addtail(_mice);

	while(!stk.is_empty()) {
		stk >> _mice;

		cout << "Pop Stack" << endl;
		d = _mice.get_dir();
		++_back_track;

		while(d<8) {
			n = _mice.next_position(d);

			if(n.get_x() == _maxx-1 && n.get_y() == _maxy-1) {
				_mice.set_dir(8);
				stk << _mice;
				lst.addtail(_mice);
				return 1;
			}

			if(is_empty(n) && !mark[n.get_y() * (_maxx-1) + n.get_x()]) {
				mark[n.get_y() * (_maxx-1) + n.get_x()] = 1;
				_mice.set_dir(d);

				stk << _mice;
				lst.addtail(_mice);
				_mice.move_direction(d);

				++_total_visit;
				d = 0;

				cout << "Move " << n.get_x() << " , " << n.get_y() << endl;
				getchar();
			} else
				++d;
		}
	}

	return 0;
}

//#define MAZE_MODULE_TEST
/*
#ifdef MAZE_MODULE_TEST

#include <iostream.h>

void main() {
	CMaze m;

	cout << m.find_solution() << endl;
}

#endif;
*/