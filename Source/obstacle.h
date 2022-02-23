#pragma once
#include "gameObject.h"

class Obstacle : public gameObject {
private:
	int size_index;
	bool is_alive, can_collide;
public:
	Obstacle();
	void rand_velocity();
	void update(Screen& screen);
	bool get_alive();
	void set_alive(bool new_alive);
	bool get_collide();
	void set_collide(bool new_collide);
	int get_index();
	void set_index(int new_index);
};