#include "Field.hpp"

Field::Field(size_t width_, size_t height_, Snake& snake_)
	:
	width(width_),
	height(height_),
	snake(snake_)
{
	field.resize((width * height));
}

std::vector<size_t>& Field::get() { return field; }

void Field::print_field() {
	dbgs << "\x1B[2J\x1B[H";
	size_t h = height;
	size_t w = width;
	for (size_t i = 0; i < h; ++i) {
		for (size_t j = 0; j < w; ++j) {
			size_t res = field[j + i * h];
			dbgs << res << " ";
		}
		dbgs << "\n";
	}
}

void Field::set_cell(size_t x, size_t y, size_t data) {
	if (x >= width || y >= height) {
		dbgs << "error\n";
		return;
	}
	field[x + y * width] = data;
}

void Field::gen_borders() {
	//horizontal
	for (size_t i = 0; i < width; ++i) {
		set_cell(i, 0, 1);
		set_cell(i, (height - 1), 1);
	}
	// vertical
	for (size_t i = 0; i < height; ++i) {
		set_cell(0, i, 1);
		set_cell((width - 1), i, 1);
	}
}

size_t Field::get_cell(size_t x, size_t y) { // TODO
	if (x >= width || y >= height) {
		throw std::runtime_error("error | (x >= width_ || y >= height_)");
		return UINT64_MAX;
	}
	return field[x + y * width];
}

static std::pair<size_t, size_t> gen(size_t xm, size_t ym) {
	size_t x = rand() % xm;
	size_t y = rand() % ym;
	return (std::make_pair(x, y));
}

void Field::gen_apple() {
	std::pair<size_t, size_t> res = gen(height, width);
	while (get_cell(res.first, res.second)) {
		res = gen(height, width);
	}
	set_cell(res.first, res.second, 2);
}

void Field::add_snake(Snake& s) {
	Head& h = s.get_Head();
	Tail& t = s.get_Tail();
	for (auto& x : field) { if ((x == 3) || (x == 4)) { x = 0; } }
	set_cell(h.get().first, h.get().second, 4);
	auto& tail_data = t.get();
	for (auto& x : tail_data) { set_cell(x.first, x.second, 3); }
}

objects Field::get_new_cell(direction d) {
	std::pair<size_t, size_t> tmp = snake.get_Head().get();
	size_t nx = 99, ny = 99, res = 99;
	objects ret;
	switch(d) {
		case (direction::eUp): 
			nx = tmp.first;
			ny = tmp.second + 1;
			res = get_cell(nx, ny);
			ret = objects(res);
			return ret;
		case (direction::eDown):
			nx = tmp.first;
			ny = tmp.second - 1;
			res = get_cell(nx, ny);
			ret = objects(res);
			return ret;
		case (direction::eLeft):
			nx = tmp.first - 1;
			ny = tmp.second;
			res = get_cell(nx, ny);
			ret = objects(res);
			return ret;
		case (direction::eRight):
			nx = tmp.first + 1;
			ny = tmp.second;
			res = get_cell(nx, ny);
			ret = objects(res);
			return ret;
		default: {}
	}
	return objects(99);
}

void Field::reset() {
	for(auto& x : field) { x = 0; }
	gen_borders();
	add_snake(snake);
}