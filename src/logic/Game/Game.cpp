#include "Game.hpp"

Game::Game()
	:
	cfg(),
	field(cfg.field_width, cfg.field_height),
	snake(cfg.snake_start_pos_x, cfg.snake_start_pos_y)
{
}

std::vector<size_t>& Game::get_field() {
	return field.get();
}

void Game::play() {
	field.gen_borders();
	field.add_snake(snake);
}

void Game::game_over() {}

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


void Game::check(size_t n) {
	bool play = true;

	switch(n) {
		case 0:
			snake.get_head().go_up();
			break;
		case 1:
			snake.get_head().go_down();
			break;
		case 2:
			snake.get_head().go_left();
			break;
		case 3:
			snake.get_head().go_right();
			break;
		default:
			break;
	}

	auto& newPos = snake.get_head().get();

	size_t res = field.get_cell(newPos.first, newPos.second);
	switch(res) {
	case 0:
		snake.get_tail().move(snake.get_head());
		break;
	}

	if (res == 0) { snake.get_tail().step(); }
	if (res == 1) { play = false; }
	if (res == 2) { snake.get_tail().grow(); }
	if (res == 3) { play = false; }
	if (res > 3) { play = false; }
	check_apple();
}