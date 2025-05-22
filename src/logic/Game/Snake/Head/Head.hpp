#ifndef MY_SNAKEHEAD
#define MY_SNAKEHEAD

#include <utility>

struct Head {
	private:
		std::pair<size_t, size_t> head;
	public:
		void go_up();
		void go_down();
		void go_left();
		void go_right();
	public:
		std::pair<size_t, size_t>& get();
		Head(size_t start_x, size_t start_y);
};

#endif
