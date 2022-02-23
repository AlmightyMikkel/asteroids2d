#include "gameObject.h"
#include "Screen.h"

int gameObject::last_id = 0;

gameObject::gameObject()
	:id(last_id++)
{
	dx = 0;
	dy = 0;
	position = { 0,0 };
	size = 10;
}


void gameObject::set_sprite(Sprite sprite) {
	this->sprite = sprite;
}

bool gameObject::input(Key key, Screen& screen) {
	return screen.IsKeyDown(key);
}

void gameObject::draw(Screen& screen) {
	screen.DrawSprite(sprite);
}


void gameObject::set_spawn_position(float x, float y) {
	this->position.x = x;
	this->position.y = y;

	sprite.position = {position.x, position.y};
}


void gameObject::warp(Screen& screen, bool warp) {
	if (warp) {
		if (position.x < 0) {
			position.x = screen.GetWindowWidth();
		}
		if (position.x > screen.GetWindowWidth()) {
			position.x = 0;
		}
		if (position.y < 0) {
			position.y = screen.GetWindowHeight();
		}
		if (position.y > screen.GetWindowHeight()) {
			position.y = 0;
		}
	}
}

Position gameObject::get_position() {
	return this->position;
}

float gameObject::get_size() {
	return this->size;
}

float gameObject::get_angle() {
	return this->sprite.angle;
}

void gameObject::set_size(float new_size) {
	this->size = new_size;
}

void gameObject::set_angle(int new_angle) {
	this->sprite.angle = new_angle;
}

void gameObject::set_origin(const float x, const float y) {
	this->sprite.origin = { x, y };
}
