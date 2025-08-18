#ifndef MY_GAMESNAKE
#define MY_GAMESNAKE

#include "../../../trash/dbg.h"
#include "../enums.hpp"
#include "Head/Head.hpp"
#include "Tail/Tail.hpp"
#include <utility>
#include <list>

struct Snake {
	private:
		Head head;
		Tail tail;
	public:
		void go(direction d, action a);
		void reset(size_t x, size_t y);
	public:
		Tail& get_Tail();
		Head& get_Head();
		Snake(size_t startx, size_t starty);
};

#endif // !MY_GAMESNAKE