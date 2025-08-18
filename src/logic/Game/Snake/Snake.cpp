#include "Snake.hpp"

Snake::Snake(size_t start_x, size_t start_y) : head(start_x, start_y), tail(head) {};

void Snake::go(direction d, action a) {
	switch (a) {
		case (action::eMove):
			tail.move();
			break;
		case (action::eGrow):
			tail.grow();
			break;
	}

	switch (d) {
		case (direction::eUp):
			head.go_up();
			break;
		case (direction::eDown):
			head.go_down();
			break;
		case (direction::eLeft):
			head.go_left();
			break;
		case (direction::eRight):
			head.go_right();
			break;
	}
}

Head& Snake::get_Head() {
	return head;
}

Tail& Snake::get_Tail() {
	return tail;
}

void Snake::reset(size_t x, size_t y) {
	tail.get().clear();
	head.get() = std::make_pair(x, y);
}
