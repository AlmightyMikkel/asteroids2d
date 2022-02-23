#include "Screen.h"
#include "game.h"
int screenWidth = 1000;
int screenHeight = 1000;


int main(int argc, char** argv)
{
	Screen screen(screenWidth, screenHeight, "Galba");
	Game game(screen);

	game.start();

	int counter = 0;
 	while (screen.IsOpen())	{
		counter++;
		screen.Clear();

		if (counter >= game.get_tick()) {
			game.update();
			counter = 0;
		}

		game.draw();

		screen.Display();
	}
	return 0;
}