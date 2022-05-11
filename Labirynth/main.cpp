#include "Game.h"

int main() {
	srand(time(nullptr));
	Game game("LABIRYNTH", 1600 , 800 , true);
	//MAIN LOOP
	while (!game.getWindowShouldClose()) {
		//UPDATE INPUT
		game.update();
		game.render();
	}

	return 0;
}