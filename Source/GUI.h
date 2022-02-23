#pragma once
#include "Screen.h"
#include <vector>

struct GUIPosition {
	const float x = 50, y = 40, offset = 50;
};

class GUI {
private:
	int score;
	std::vector<Sprite> healths;
	int health_amount;
	GUIPosition position;
public:
	GUI();
	void start(Sprite& sprite);
	void draw(Screen& screen);
	void add_score(int _score);
	void set_lifes(int health);
	void remove_life();
	GUIPosition get_position();
};