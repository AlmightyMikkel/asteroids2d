#pragma once
#include "Screen.h"
#include "spaceship.h"
#include "obstacle.h"
#include "bullet.h"
#include "GUI.h"
#include <vector>


class Game {
private:
	Screen& screen;
	Spaceship spaceship;
	Spaceship ufo;
	GUI gui;
	int target_tick, current_tick;
	bool is_running;
	std::vector<Obstacle> asteroids;
	std::vector<Bullet> bullets;
	std::vector<Bullet> ufo_bullets;
	Sprite background;
	Sprite sprite_spaceship;
	Sprite sprite_ufo;
	Sprite sprite_asteroid;
	Sprite sprite_bullet;
	Sprite sprite_health;
	Sound sound_background, sound_ability, sound_moving, sound_shooting;
	bool check_collision(gameObject& a, gameObject& b);
public:
	Game(Screen& screen);
	void handle_collision();
	int get_tick();
	bool get_running();
	void set_running(bool new_value);
	void start();
	void update();
	void draw();
	void game_over_draw(std::string test);
};