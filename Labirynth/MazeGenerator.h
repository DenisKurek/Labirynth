#pragma once
#include<iostream>
#include<vector>
#include<array>
#include <windows.h> 
#include <time.h>
#include <set>
#include <algorithm>
constexpr int BOARD_SIZE = 20;

// creates logical representation of maze size BOARD_HEIGHT BOARD_WIDTH
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

	//generates maze
	void dfs(int x, int y);

	//draws maze in console
	void draw();

public:
	MazeGenerator() {
		dfs(0, 0);
		draw();
	}

	int getSize() { return BOARD_SIZE; }

	bool getWall(int x, int y, char wall);

	Matrix<Cell, BOARD_SIZE, BOARD_SIZE> matrix;
};
