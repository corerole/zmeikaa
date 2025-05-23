#include "Game.hpp"

Game::Game()
	:
	cfg(),
	snake(cfg.snake_start_pos_x, cfg.snake_start_pos_y),
	field(cfg.field_width, cfg.field_height, snake)
{
	prepare();
}

Field& Game::get_Field() {
	return field;
}

Snake& Game::get_Snake() {
	return snake;
}

void Game::prepare() {
	field.gen_borders();
	field.add_snake(snake);
	play = 1;
}

static size_t step_to_apple = 5;
static bool apple() {
	static size_t apple_ctr = 0;
	if (!(apple_ctr % step_to_apple)) {
		return true;
	}
	apple_ctr++;
	return false;
}

void Game::check_apple() {
	if (apple()) {
		field.add_snake(snake);
		field.gen_apple();
	}
	else {
		field.add_snake(snake);
	}
}

static direction to_direction(int glfw_keycode) {
	switch(glfw_keycode) {
		case (GLFW_KEY_W): return direction::eUp;
		case (GLFW_KEY_A): return direction::eLeft;
		case (GLFW_KEY_S): return direction::eDown;
		case (GLFW_KEY_D): return direction::eRight;
	}
	return direction::eUnknown;
}

static action reaction(objects in) {
	switch (in) {
		case (objects::eClear):	return action::eMove;
		case (objects::eApple): return action::eGrow;
		case (objects::eWall): return action::eGameOver;
		case (objects::eTail): return action::eGameOver;
		case (objects::eHead): return action::eGameOver;
		default: {}
	}
	return action::eGameOver;
}

void Game::process(int glfw_keycode) {
	if(!play) {return;}
	direction dire = to_direction(glfw_keycode);
	dbgs << "Direction: " << size_t(dire) << " | ";
	objects res = field.get_new_cell(dire);
	dbgs << "Object: " << size_t(res) << " | ";
	action act = reaction(res);
	dbgs << "Action: " << size_t(act) << "\n";
	if(act == action::eGameOver) { play = false; return; }
	snake.go(dire, act);
	check_apple();
	field.print_field();
}