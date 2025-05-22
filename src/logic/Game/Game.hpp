#ifndef MY_GAMEHPP
#define MY_GAMEHPP

#include "Snake/Snake.hpp"
#include "Field/Field.hpp"

struct GameSettings {
	public:
		size_t field_height = 10;
		size_t field_width = 10;
		size_t snake_start_pos_x = 3;
		size_t snake_start_pos_y = 3;
};

struct Game {
	private:
		Field field;
		Snake snake;
	public:
		Game();
	public:
		GameSettings cfg;
		std::vector<size_t>& get_field();
		void play();
		void check(size_t userinput);
		void check_apple();
		void game_over();
};

#endif // !MY_GAMEHPP