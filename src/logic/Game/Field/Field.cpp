#include "Field.hpp"

std::vector<size_t>& Field::get() { return field_; }

void Field::print_field() {
	size_t h = height_;
	size_t w = width_;
	for (size_t i = 0; i < h; ++i) {
		for (size_t j = 0; j < w; ++j) {
			size_t res = field_[j + i * h];
			dbgs << res << " ";
		}
		dbgs << "\n";
	}
}

void Field::set_cell(size_t x, size_t y, size_t data) {
	if (x >= width_ || y >= height_) {
		dbgs << "error\n";
		return;
	}
	field_[x + y * width_] = data;
}

Field::Field(size_t width, size_t height) {
	width_ = width; height_ = height;
	field_.resize((width * height));
}

void Field::gen_borders() {
	//horizontal
	for (size_t i = 0; i < width_; ++i) {
		set_cell(i, 0, 1);
		set_cell(i, (height_ - 1), 1);
	}
	// vertical
	for (size_t i = 0; i < height_; ++i) {
		set_cell(0, i, 1);
		set_cell((width_ - 1), i, 1);
	}
}

size_t Field::get_cell(size_t x, size_t y) { // TODO
	if (x >= width_ || y >= height_) {
		throw std::runtime_error("error | (x >= width_ || y >= height_)");
		return UINT64_MAX;
	}
	return field_[x + y * width_];
}

static std::pair<size_t, size_t> gen(size_t xm, size_t ym) {
	size_t x = rand() % xm;
	size_t y = rand() % ym;
	return (std::make_pair(x, y));
}

void Field::gen_apple() {
	std::pair<size_t, size_t> res = gen(height_, width_);
	while (get_cell(res.first, res.second)) {
		res = gen(height_, width_);
	}
	set_cell(res.first, res.second, 2);
}

void Field::add_snake(Snake& s) {
	std::pair<size_t, size_t>& h = s.get_head();
	std::list<std::pair<size_t, size_t>>& t = s.get_tail();
	for (auto& x : field_) { if ((x == 3) || (x == 4)) { x = 0; } }
	set_cell(h.first, h.second, 4);
	for (auto x : t) { set_cell(x.first, x.second, 3); }
}

