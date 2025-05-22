#include "Head.hpp"

void Head::go_up() {
	head.first; // x
	head.second--; // y
}

void Head::go_down() {
	head.first;
	head.second++;
}

void Head::go_left() {
	--head.first;
	head.second;
}

void Head::go_right() {
	head.first++;
	head.second;
}

std::pair<size_t, size_t>& Head::get() {
	return head;
}

Head::Head(size_t start_x, size_t start_y) : head(std::make_pair(start_x, start_y)) {}
