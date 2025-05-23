#include "Tail.hpp"

void Tail::move() {
	grow();
	tail.pop_back();
}

void Tail::grow() {
	tail.push_front(tailhead.get());
}

std::list<std::pair<size_t, size_t>>& Tail::get() {
	return tail;
}