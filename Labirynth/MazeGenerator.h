#pragma once
#include<iostream>
#include<vector>
#include<array>
#include <windows.h> 
#include <time.h>
#include <set>
#include <algorithm>
constexpr int BOARD_HEIGHT = 20;
constexpr int BOARD_WIDTH = 20;

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
	};

	void dfs(int x, int y);

	void draw();

public:
	MazeGenerator() {
		dfs(0, 0);
		draw();
	}

	bool getWall(int x, int y, char wall);

	Matrix<Cell, BOARD_HEIGHT, BOARD_WIDTH> matrix;
};
