#include"MazeGenerator.h"

void MazeGenerator::dfs(int x, int y) {
	this->matrix(x, y).visited = true;
	/*draw(matrix, matrix.width, matrix.height);
	Sleep(10);*/
	std::vector<int> vec = { 1,2,3,4 };
	std::random_shuffle(vec.begin(), vec.end());

	while (vec.size()) {
		switch (vec.back()) {
		case 1:
			if (x + 1 < this->matrix.height && this->matrix(x + 1, y).visited == false) {
				this->matrix(x, y).down = false;
				this->matrix(x + 1, y).up = false;
				dfs(x + 1, y);
			}
			break;
		case 2:
			if (y + 1 < this->matrix.width && this->matrix(x, y + 1).visited == false) {
				this->matrix(x, y).right = false;
				this->matrix(x, y + 1).left = false;
				dfs(x, y + 1);
			}
			break;
		case 3:
			if (x - 1 >= 0 && this->matrix(x - 1, y).visited == false) {
				this->matrix(x, y).up = false;
				this->matrix(x - 1, y).down = false;
				dfs(x - 1, y);
			}
			break;
		case 4:
			if (y - 1 >= 0 && this->matrix(x, y - 1).visited == false) {
				this->matrix(x, y).left = false;
				this->matrix(x, y - 1).right = false;
				dfs(x, y - 1);
			}
		}
		vec.pop_back();
	}
	return;
}

void MazeGenerator::draw() {
	system("cls");
	std::cout << (char)197;
	for (int j = 0; j < BOARD_HEIGHT - 1; j++) {
		std::cout << (char)196 << (char)197;
	}
	std::cout << (char)196 << (char)197 << std::endl;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		std::cout << (char)197;
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (this->matrix(i, j).right) {
				std::cout << ' ' << (char)179;
			}
			else {
				std::cout << "  ";
			}
		}
		std::cout << std::endl << (char)197;
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (this->matrix(i, j).down) {
				std::cout << (char)196 << (char)197;
			}
			else {
				std::cout << ' ' << (char)197;
			}
		}
		std::cout << std::endl;

	}

}

bool MazeGenerator::getWall(int x, int y, char wall) {
	switch (wall) {
	case 'L':
		return  this->matrix(x, y).left;
	case 'R':
		return  this->matrix(x, y).right;
	case 'U':
		return  this->matrix(x, y).up;
	case 'D':
		return  this->matrix(x, y).down;
	}
}