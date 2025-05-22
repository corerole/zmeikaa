#ifndef MY_FIELD
#define MY_FIELD

#include <vector>
#include "../Snake/Snake.hpp"
#include "../../../trash/dbg.h"
#include <random>
#include <stdexcept>

struct Field {
private:
	size_t height_ = 1;
	size_t width_ = 1;
	std::vector<size_t> field_;
public:
	void print_field();
	void gen_borders();
	void gen_apple();
	void add_snake(Snake& s);
	std::vector<size_t>& get();
	void set_cell(size_t x, size_t y, size_t data);
	size_t get_cell(size_t x, size_t y);
public:
	Field(size_t width, size_t height);
};

#endif