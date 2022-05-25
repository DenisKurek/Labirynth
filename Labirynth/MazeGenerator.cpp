#include "MazeGenerator.hpp"

MazeGenerator::MazeGenerator() {
	//dfs(0, 0);
	kruskal();
	draw();
}

int MazeGenerator::getSize() const {
	return BOARD_SIZE;
}

bool MazeGenerator::getWall(int x, int y, Wall wall) {
	switch (wall) {
		case WLEFT:
			return this->matrix(x, y).left;
		case WRIGHT:
			return this->matrix(x, y).right;
		case WUP:
			return this->matrix(x, y).up;
		case WDOWN:
			return this->matrix(x, y).down;
		default:
			return true;
	}
}

void MazeGenerator::dfs(int x, int y) {
	this->matrix(x, y).visited = true;

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
}

void MazeGenerator::kruskal() {
	std::vector<std::pair<int, Wall>> connections;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (i - 1 >= 0) {
				connections.push_back(std::make_pair(i * BOARD_SIZE + j, WUP));
			}
			if (j - 1 >= 0) {
				connections.push_back(std::make_pair(i * BOARD_SIZE + j, WLEFT));
			}
			group[i * BOARD_SIZE + j] = i * BOARD_SIZE + j;
		}
	}

	std::random_shuffle(connections.begin(), connections.end());

	for (int i = 0; i < connections.size(); i++) {
		if (connections[i].second == WUP) {
			int a = connections[i].first;
			int b = a - BOARD_SIZE;

			if (find(a) != find(b)) {
				unite(a, b);
				int x = a / BOARD_SIZE;
				int y = a % BOARD_SIZE;
				this->matrix(x, y).up = false;
				this->matrix(x - 1, y).down = false;
			}
		} else {
			int a = connections[i].first;
			int b = a - 1;

			if (find(a) != find(b)) {
				unite(a, b);
				int x = a / BOARD_SIZE;
				int y = a % BOARD_SIZE;
				this->matrix(x, y).left = false;
				this->matrix(x, y - 1).right = false;
			}
		}
	}
}

int MazeGenerator::find(int a) {
	return group[a] = (group[a] == a ? a : find(group[a]));
}

void MazeGenerator::unite(int a, int b) {
	group[find(a)] = find(b);
}

void MazeGenerator::draw() {
	system("cls");

	std::cout << (char)197;

	for (int j = 0; j < BOARD_SIZE - 1; j++) {
		std::cout << (char)196 << (char)197;
	}

	std::cout << (char)196 << (char)197 << '\n';

	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << (char)197;

		for (int j = 0; j < BOARD_SIZE; j++) {
			if (this->matrix(i, j).right) {
				std::cout << ' ' << (char)179;
			} else {
				std::cout << "  ";
			}
		}

		std::cout << '\n' << (char)197;

		for (int j = 0; j < BOARD_SIZE; j++) {
			if (this->matrix(i, j).down) {
				std::cout << (char)196 << (char)197;
			} else {
				std::cout << ' ' << (char)197;
			}
		}
		std::cout << '\n';
	}
}
