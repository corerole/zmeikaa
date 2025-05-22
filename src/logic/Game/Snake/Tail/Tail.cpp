#include "Tail.hpp"

void Tail::move(Head& head) {
	grow(head);
	tail.pop_back();
}

void Tail::grow(Head& Head) {
	tail.push_front(Head.get());
}

std::list<std::pair<size_t, size_t>>& Tail::get() {
	return tail;
}