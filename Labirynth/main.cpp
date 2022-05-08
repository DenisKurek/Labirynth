#include "Game.h"

int main() {
	Game game("LABIRYNTH", 640 , 480 , true);
	//MAIN LOOP
	while (!game.getWindowShouldClose()) {
		//UPDATE INPUT
		game.update();
		game.render();
	}

	return 0;
}