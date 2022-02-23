#pragma once
#include "gameObject.h"

class Spaceship : public gameObject {
private:
	float shoot_cooldown, curr_shoot;
	float ability_cooldown, curr_ability;
	float ufo_wait_time, ufo_curr;
	float immune_time, curr_immune;
	bool is_alive, can_shoot, can_ability;
	int lifes;
public:
	Spaceship();
	void update(Screen& screen);
	void ufo(Screen& screen);
	void shoot();
	void ability(Screen& screen);
	void set_shot(bool new_bool);
	void TakeDamage(int dmg);
	void set_alive(bool new_bool);
	bool get_alive();
	bool on_collision();
	bool can_shot();
	bool ability_ready();
	int get_lifes();

};