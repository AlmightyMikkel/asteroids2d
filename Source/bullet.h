#pragma once
#include "gameObject.h"

class Bullet : public gameObject {
private:
	bool is_alive; 
	float curr, life_time;
public:
	Bullet();
	void start(float angle, Position start_position);
	void update(Screen& screen);
	bool get_alive(); 
	void set_alive(bool new_alive);
};