#pragma once
#include "Screen.h"
#include <iostream>

struct Position {

	float x, y;

};

class gameObject {
protected:
	Position position;
	Sprite sprite;
	int id;
	static int last_id;
	float dx, dy;
	float size;
public:
	gameObject();
	void set_sprite(Sprite sprite);
	void set_origin(const float x, const float y);
	void draw(Screen& screen);
	float get_angle();
	void set_angle(int new_angle);
	void set_spawn_position(float x, float y);
	void warp(Screen& screen, bool warp);
	bool input(Key key, Screen& screen);
	float get_size();
	void set_size(float new_size);
	Position get_position();

};