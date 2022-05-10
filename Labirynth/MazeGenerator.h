#pragma once
#include<iostream>
#include<vector>
#include<array>
#include <windows.h> 
#include <time.h>
#include <set>
#include <algorithm>

constexpr int BOARD_HEIGHT = 10;
constexpr int BOARD_WIDTH = 10;
class MazeGenerator {
	class Cell {
	private:
		static constexpr int NUMBER_OF_WALLS = 4;
	public:
		bool left = true, right = true, up = true, down = true;
		bool visited = false;
	};

	template<class T, size_t rows, size_t cols>
	class Matrix
	{
		std::array<T, rows* cols> m_Data;
	public:
		unsigned width = rows;
		unsigned height = cols;
		T& operator()(size_t y, size_t x)
		{
			return m_Data[y * cols + x];
		}

		// more methods go here
	};

	void dfs(int x, int y) {
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
					dfs( x + 1, y);
				}
				break;
			case 2:
				if (y + 1 < this->matrix.width && this->matrix(x, y + 1).visited == false) {
					this->matrix(x, y).right = false;
					this->matrix(x, y + 1).left = false;
					dfs( x, y + 1);
				}
				break;
			case 3:
				if (x - 1 >= 0 && this->matrix(x - 1, y).visited == false) {
					this->matrix(x, y).up = false;
					this->matrix(x - 1, y).down = false;
					dfs( x - 1, y);
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

	void draw() {
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




public:
	MazeGenerator() {
		dfs(0, 0);
		draw();
	}

	bool getWall(int x, int y, char wall) {
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



	Matrix<Cell, BOARD_HEIGHT, BOARD_WIDTH> matrix;
};
