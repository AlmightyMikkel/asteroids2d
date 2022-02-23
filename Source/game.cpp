#include "Screen.h"
#include "game.h"
#include <time.h>



Game::Game(Screen& screen)
	:screen(screen)
{

	target_tick = 1;
	current_tick = 0;

	set_running(true);

	sound_background = screen.LoadSound("assets/background_music.wav");
	sound_shooting = screen.LoadSound("assets/space_shot.wav");
	sound_ability = screen.LoadSound("assets/ship_ability.wav");


	sprite_spaceship = screen.LoadSprite("assets/spaceship.png");
	sprite_asteroid = screen.LoadSprite("assets/asteroid.png");
	sprite_bullet = screen.LoadSprite("assets/bullet.png");
	background = screen.LoadSprite("assets/space.png");
	sprite_ufo = screen.LoadSprite("assets/ufo.png");
	sprite_health = screen.LoadSprite("assets/health.png");

	sound_background.looping = true;

	sprite_spaceship.origin = { 25,25 };
	sprite_ufo.origin = { 25,25 };

}

void Game::start() {
	srand((unsigned int)time(0));

	gui.set_lifes(spaceship.get_lifes());

	spaceship.set_sprite(sprite_spaceship);
	spaceship.set_size(20);
	ufo.set_sprite(sprite_ufo);
	ufo.set_size(20);

	ufo.set_spawn_position(200, 200);

	gui.start(sprite_health);

	for (int i = 0; i < 5; i++) {
		Obstacle temp = Obstacle();
		temp.set_sprite(sprite_asteroid);
		asteroids.push_back(temp);
		temp.set_origin(25, 25);
	}

	screen.PlaySound(sound_background);
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i].set_spawn_position((float)(rand() % screen.GetWindowWidth() / 2), (float)(rand() % screen.GetWindowHeight() / 2));
	}
}

void Game::handle_collision() {

	for (auto& asteroid : asteroids) {
		if (check_collision(asteroid, spaceship)) {
			if (spaceship.on_collision()) {
				gui.remove_life();
			}
		}
	}

	std::vector<Obstacle> temp_ast;

	for (auto& bullet : bullets) {
		for (auto& asteroid : asteroids) {
			if (check_collision(bullet, asteroid)) {
				if (asteroid.get_index() > 1) {
					asteroid.set_index(asteroid.get_index() - 1);
					Obstacle new_asteroid = asteroid;
					new_asteroid.rand_velocity();
					temp_ast.push_back(new_asteroid);
					bullet.set_alive(false);
					gui.add_score(100);
				}
				else if (asteroid.get_index() == 1) {
					bullet.set_alive(false);
					asteroid.set_alive(false);
					gui.add_score(200);
				}
			}
		}
	}

	asteroids.insert(asteroids.end(), temp_ast.begin(), temp_ast.end());

	for (auto& bullet : ufo_bullets) {
		if (check_collision(bullet, spaceship)) {
			bullet.set_alive(false);
			std::cout << "UFO BULLETS HIT ME" << std::endl;
			if (spaceship.on_collision()) {
				gui.remove_life();
			}
		}
	}

	for (auto& bullet : bullets) {
		if (check_collision(bullet, ufo))
		{
			ufo.on_collision();
		}
	}

	if (check_collision(ufo, spaceship)) {
		std::cout << "UFO HIT ME" << std::endl;

		if (spaceship.on_collision()) {
			gui.remove_life();
		}
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].set_collide(true);
	}
}

bool Game::check_collision(gameObject& a, gameObject& b) {
	Position a_pos = a.get_position();
	Position b_pos = b.get_position();

	float a_size = a.get_size();
	float b_size = b.get_size();

	return ((b_pos.x - a_pos.x) * (b_pos.x - a_pos.x)
		+ (b_pos.y - a_pos.y) * (b_pos.y - a_pos.y)
		< (a_size + b_size) * (a_size + b_size));
}

void Game::update() {

	if (spaceship.get_lifes() <= 0) {
		//game_over_draw("ded");
		spaceship.set_alive(false);
	}

	if (ufo.get_lifes() <= 0) {
		gui.add_score(100);
		ufo.set_alive(false);
	}

	current_tick++;

	if (get_running()) {
		if (current_tick >= target_tick) {
			current_tick = 0;
		}

		for (int i = 0; i < asteroids.size(); i++) {
			asteroids[i].update(screen);

		}

		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].get_alive()) {
				bullets[i].update(screen);
			}
		}

		for (int i = 0; i < ufo_bullets.size(); i++) {
			if (ufo_bullets[i].get_alive()) {
				ufo_bullets[i].update(screen);
			}
		}

		if (screen.IsKeyDown(Key::Space) && spaceship.can_shot()) {
			screen.PlaySound(sound_shooting);
			spaceship.shoot();
			Bullet temp = Bullet();
			temp.set_sprite(sprite_bullet);
			temp.start(spaceship.get_angle(), spaceship.get_position());
			bullets.push_back(temp);
		}

		if (screen.IsKeyDown(Key::Q) && spaceship.ability_ready())
		{
			screen.PlaySound(sound_ability);
			spaceship.ability(screen);
		}


		if (ufo.can_shot()) {
			ufo.set_shot(false);
			Bullet temp = Bullet();
			temp.set_sprite(sprite_bullet);
			temp.start(90, ufo.get_position()); //get the angle between ufo and ship
			ufo_bullets.push_back(temp);

		}


		std::erase_if(bullets, [](auto& bullet) ->bool {return !bullet.get_alive(); });
		std::erase_if(ufo_bullets, [](auto& bullet) ->bool {return !bullet.get_alive(); });
		std::erase_if(asteroids, [](auto& asteroid) ->bool {return !asteroid.get_alive(); });


		spaceship.update(screen);
		

		if (ufo.get_alive()) {
			ufo.ufo(screen);
			ufo.shoot();

		}

		handle_collision();

	}

}

void Game::draw() {
	screen.DrawSprite(background);

	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i].draw(screen);
	}
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].get_alive()) {
			bullets[i].draw(screen);
		}
	}
	for (int i = 0; i < ufo_bullets.size(); i++) {
		if (ufo_bullets[i].get_alive()) {
			ufo_bullets[i].draw(screen);
		}
	}


	spaceship.draw(screen);

	if (ufo.get_alive())
	{
		ufo.draw(screen);
	}

	gui.draw(screen);

}


void Game::game_over_draw(std::string test) {
	std::cout << test << std::endl;
	screen.DrawText(300, 500, { 255,255,255,255 }, "GAME OVER!", 3);
	screen.DrawText(400, 700, { 255,255,255,255 }, "Press 'Enter' to play again!");
}

int Game::get_tick() {
	return this->current_tick;
}


bool Game::get_running() {
	return this->is_running;
}

void Game::set_running(bool new_value) {
	this->is_running = new_value;
}