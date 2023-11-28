#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cmaze.h"
#include "my_assert.h"

CMaze::CMaze(int maxx, int maxy) {
	_maze = NULL;
	resize_maze(maxx, maxy);
}

CMaze::~CMaze() {
	if(_maze != NULL)
		delete [] _maze;

	_maze = NULL;
}

int CMaze::is_empty(int x, int y) {
	ASSERT(x >= 0 && x < _maxx);
	ASSERT(y >= 0 && y < _maxy);
	
	if(_maze[(_maxx - 1) * y + x] == EMPTY)
		return true;
	
	return false;
}

int CMaze::is_empty(CPosition &pos) {
	int x,y;

	x = pos.get_x();
	y = pos.get_y();
	ASSERT(x >= 0 && x < _maxx);
	ASSERT(y >= 0 && y < _maxy);
	
	if(_maze[(_maxx - 1) * y + x] == EMPTY)
		return true;
	
	return false;
}


int CMaze::resize_maze(int maxx, int maxy) {
	ASSERT(maxx > 5 && maxy > 5);
	int seed = 8;

    int i, j,k;

	if(_maze != NULL)
		delete [] _maze;

	_maze = new int[maxx * maxy];

	if(_maze == NULL) {
		_maxx = 0;
		_maxy = 0;

		return false;
	}

	_maxx = maxx;
	_maxy = maxy;

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
	return true;
}

int CMaze :: find_solution() {
	int *mark;
	int d;
	CPosition n;

	mark = new int[_maxx * _maxy];
	if(mark == NULL)
		return -1;

	for(int i=0;i<_maxy;++i)
		for(int j=0;j<_maxx;++j)
			mark[i * (_maxx-1) + j] = 0;

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
				return 1;
			}

			if(is_empty(n) && !mark[n.get_y() * (_maxx-1) + n.get_x()]) {
				mark[n.get_y() * (_maxx-1) + n.get_x()] = 1;
				_mice.set_dir(d+1);

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

#define MAZE_MODULE_TEST
#ifdef MAZE_MODULE_TEST

#include <iostream.h>

void main() {
	CMaze m;

	cout << m.find_solution() << endl;
}

#endif;