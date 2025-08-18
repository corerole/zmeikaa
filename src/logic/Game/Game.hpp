#ifndef MY_GAMEHPP
#define MY_GAMEHPP

#include "Snake/Snake.hpp"
#include "Field/Field.hpp"
#include "glfw_key_def.hpp"
#include "enums.hpp"

struct GameSettings {
	public:
		size_t field_height = 10;
		size_t field_width = 10;
		size_t snake_start_pos_x = 3;
		size_t snake_start_pos_y = 3;
};

struct Game {
	public:
		GameSettings cfg;
	private:
		Snake snake;
		Field field;
		bool play = 0;
	public:
		void process(int glfw_keycode);
		void reset();
	public:
		Field& get_Field();
		Snake& get_Snake();
		Game();
	public:
		void prepare();
		void check_apple();
};

#endif // !MY_GAMEHPP