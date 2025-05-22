#include "Snake.hpp"

Snake::Snake(size_t start_x, size_t start_y) : head(start_x, start_y), tail(head) {};

void Snake::move() {
	tail.move(head);
}

void Snake::grow() {
	tail.grow(head);
}

Head& Snake::get_head() {
	return head;
}

Tail& Snake::get_tail() {
	return tail;
}

