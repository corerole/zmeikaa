#ifndef MY_SNAKETAIL
#define MY_SNAKETAIL

#include <list>
#include <utility>
#include "../Head/Head.hpp"
#include "../../../../trash/dbg.h"

struct Tail {
	private:
		std::list<std::pair<size_t, size_t>> tail;
	private:
		Head& tailhead;
	public:
		Tail(Head& head) : tailhead(head) {};
		std::list<std::pair<size_t, size_t>>& get();
		void move();
		void grow();
};

#endif