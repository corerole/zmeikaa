#ifndef MY_GAMESNAKE
#define MY_GAMESNAKE

#include "../../../trash/dbg.h"
#include "Head/Head.hpp"
#include "Tail/Tail.hpp"
#include <utility>
#include <list>

struct XY {
	size_t x = 0;
	size_t y = 0;
};

struct Snake {
	private:
		Head head;
		Tail tail;
	public:
		void move();
		void grow();
	public:
		Tail& get_tail();
		Head& get_head();
		Snake(size_t startx, size_t starty);
};

#endif // !MY_GAMESNAKE