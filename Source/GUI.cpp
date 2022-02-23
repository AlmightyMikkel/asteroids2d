#include "GUI.h"

GUI::GUI()
{
	health_amount = 1;

	score = 0;
}


void GUI::start(Sprite& sprite) {
	for (int i = 0; i < health_amount; i++)
	{
		healths.push_back(sprite);
	}
}

void GUI::draw(Screen& screen) {
	screen.DrawText(50, 10, { 255,255,255 }, "SCORE: " + std::to_string(score), 2);
	for (int i = 0; i < health_amount; i++)
	{
		healths[i].position = { get_position().x + (get_position().offset * i), get_position().y};
		screen.DrawSprite(healths[i]);
	}
}

void GUI::add_score(int _score) {
	score += _score;
}

GUIPosition GUI::get_position() {
	return this->position;
}

void GUI::set_lifes(int health) {
	this->health_amount = health;
}

void GUI::remove_life() {
	this->health_amount -= 1;
}