#ifndef MY_FIELD
#define MY_FIELD

#include <vector>
#include "../enums.hpp"
#include "../Snake/Snake.hpp"
#include "../../../trash/dbg.h"
#include <random>
#include <stdexcept>

struct Field {
	private:
		size_t height = 1;
		size_t width = 1;
		std::vector<size_t> field;
	private:
		Snake& snake;
	public:
		objects get_new_cell(direction dir);
	public:
		void print_field();
		void gen_borders();
		void gen_apple();
		void add_snake(Snake& s);
		std::vector<size_t>& get();
		void set_cell(size_t x, size_t y, size_t data);
		size_t get_cell(size_t x, size_t y);
	public:
		Field(size_t width_, size_t height_, Snake& snake_);
};

#endif