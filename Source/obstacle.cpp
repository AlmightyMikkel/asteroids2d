#include "obstacle.h"

Obstacle::Obstacle()
	:gameObject()
{
	position = { 400 , 0 };
	dx = rand() % 9 - 3;
	dy = rand() % 9 - 3;
	set_index(3);
}

void Obstacle::rand_velocity() {
	dx = rand() % 9 - 3;
	dy = rand() % 9 - 3;
}

void Obstacle::update(Screen& screen) {
	sprite.scale = size_index;

	position.x += dx;
	position.y += dy;

	sprite.position = {position.x - (get_size() / 2), position.y - (get_size() / 2) };

	warp(screen, true);
}

int Obstacle::get_index() {
	return this->size_index;
}

void Obstacle::set_index(int new_index) {
	this->size_index = new_index;
	set_size(16.66 * this->size_index);
}

bool Obstacle::get_alive() {
	return this->is_alive;
}
void Obstacle::set_alive(bool new_alive) {
	this->is_alive = new_alive;
}

bool Obstacle::get_collide() {
	return this->can_collide;
}

void Obstacle::set_collide(bool new_collide) {
	this->can_collide = new_collide;
}
