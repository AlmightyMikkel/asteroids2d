#include "bullet.h"

Bullet::Bullet()
	:gameObject()
{
	position = { 0 , 0 };
	dx = rand() % 9 - 3.0f;
	dy = rand() % 9 - 3.0f;
	size = 10;
	life_time = 200;
	curr = 0;
	is_alive = true;
}

void Bullet::start(float angle, Position start_position) {
	is_alive = true;

	position = start_position;
	sprite.angle = angle;

	dx = std::cos(angle * 0.017453f) * 5;
	dy = std::sin(angle * 0.017453f) * 5;

}

void Bullet::update(Screen& screen) {
	if (!is_alive){
		return;
	}
	position.x += dx;
	position.y += dy;

	sprite.position = {position.x, position.y};
	
	warp(screen, true);
	
	if (curr >= life_time) {
		is_alive = false;
	}

	curr++;
}


bool Bullet::get_alive() {
	return this->is_alive;
}

void Bullet::set_alive(bool new_alive) {
	this->is_alive = new_alive;
}