#include "spaceship.h"

Spaceship::Spaceship()
	:gameObject()

{
	position = { 900, 900 };
	ability_cooldown = 300;
	shoot_cooldown = 30;
	ufo_wait_time = 300;
	curr_shoot = shoot_cooldown - 1;
	curr_ability = ability_cooldown - 1;
	ufo_curr = ufo_wait_time - 1;
	immune_time = 100;
	curr_immune = 0;
	size = 20;

	can_shoot = true;
	can_ability = true;
	is_alive = true;
	lifes = 3;

}

void Spaceship::update(Screen& screen) {

	if (input(Key::Up, screen)) {
		dx += std::cos(sprite.angle * 0.017453f)* 0.2;
		dy += std::sin(sprite.angle * 0.017453f) * 0.2;
	}

	if (input(Key::Left, screen)) {
		sprite.angle -= 3;
	}
	if (input(Key::Right, screen)) {
		sprite.angle += 3;
	}

	warp(screen, true);
	position.x += dx;
	position.y += dy;
	sprite.position = { position.x, position.y };

	curr_ability++;
	curr_shoot++;
	curr_ability++;
	
	if (curr_immune > 0) {
		curr_immune--;
	} 

	if (curr_shoot >= shoot_cooldown) {
		can_shoot = true;
	}

	if (curr_ability >= ability_cooldown)
	{
		can_ability = true;
	}
}

void Spaceship::ufo(Screen& screen) {

	if (ufo_curr >= ufo_wait_time) {

		int x = rand() % 100;
		if (x % 2 == 0) {
			dx = rand() % screen.GetWindowWidth() / 200;
			dy = rand() % screen.GetWindowHeight() / 200;
		} else {

			dx = rand() % (screen.GetWindowWidth() / 200) * -1;
			dy = rand() % (screen.GetWindowWidth() / 200) * -1;
		}


		ufo_curr = 0;
	}

	position.x += dx;
	position.y += dy;

	sprite.position = { position.x, position.y };
	warp(screen, true);
	ufo_curr++;
	curr_shoot++;

	if (curr_shoot >= shoot_cooldown) {
		can_shoot = true;
		shoot();
	}
}

bool Spaceship::on_collision() {

	if (curr_immune <= 0)
	{
		TakeDamage(1);
		std::cout << "ASTEROID HIT ME" << std::endl;
		curr_immune = immune_time;
		return true;
	}
	else
	{
		return false;
	}

}

void Spaceship::ability(Screen& screen) {
	position.x = rand() % screen.GetWindowWidth();
	position.y = rand() % screen.GetWindowHeight();
	curr_ability = 0;
	can_ability = false;
}


void Spaceship::shoot() {
	curr_shoot = 0;
	can_shoot = false;
}

void Spaceship::set_shot(bool new_bool) {
	this->can_shoot = new_bool;
}

bool Spaceship::get_alive() {
	return this->is_alive;
}

bool Spaceship::can_shot() {
	return this->can_shoot;
}
bool Spaceship::ability_ready() {
	return this->can_ability;
}

void Spaceship::TakeDamage(int dmg) {
	this->lifes -= dmg;
}

int Spaceship::get_lifes() {
	return this->lifes;
}

void Spaceship::set_alive(bool new_bool) {
	this->is_alive = new_bool;
}