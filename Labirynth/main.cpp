#include "Game.hpp"

int main() {
	srand(time(nullptr));

	Game game("Labirynth", 1600, 800, true);

	// Main game loop
	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
	}

	return 0;
}
