#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr int BOARD_SIZE = 50;

enum Wall {
	WLEFT = 0,
	WRIGHT,
	WUP,
	WDOWN
};

/**
 * Class responsible for the generation of the maze.
 */
class MazeGenerator {
private:
	/**
	 * Class that defines a single maze cell.
	 */
	class Cell {
	private:
		static constexpr int NUMBER_OF_WALLS = 4;

	public:
		bool left = true, right = true, up = true, down = true;
		bool visited = false;
	};

	/**
	 * Class that defines a matrix that may store multiple maze cells.
	 */
	template<class T, size_t rows, size_t cols>
	class Matrix {
	private:
		std::array<T, rows* cols> m_Data;

	public:
		unsigned width = rows;
		unsigned height = cols;

		/**
		 * An overloaded function call operator that allows for a more convenient
		 *     access to a specific cell at certain x and y positions.
		 */
		T& operator()(size_t y, size_t x) {
			return m_Data[y * cols + x];
		}
	};

	Matrix<Cell, BOARD_SIZE, BOARD_SIZE> matrix;
	int group[BOARD_SIZE * BOARD_SIZE + 1];

public:
	/**
	 * The default constructor that initiates the maze generation process for a particular object.
	 */
	MazeGenerator();

	/**
	 * Gets and returns the size of the maze.
	 * @return The size of the maze.
	 */
	int getSize() const;

	/**
	 * Gets and returns whether the specified cell at the provided
	 *     x and y positions has the specified wall or not.
	 * @param x The x position of the cell for which to look for wall information.
	 * @param y The y position of the cell for which to look for wall information.
	 * @param wall A predefined wall which state is to be checked.
	 */
	bool getWall(int x, int y, Wall wall);

private:
	/**
	 * Depth-first search algorithm that generates a maze with random corridors.
	 * @param x The starting x position from which the maze is to be generated.
	 * @param y The starting y position from which the maze is to be generated.
	 */
	void dfs(int x, int y);

	/**
	 * Kruskal's algorithm that generates a maze with random corridors.
	 */
	void kruskal();

	/**
	 * Checks, which group the given room belongs to.
	 * @param a A room ID.
	 */
	int find(int a);

	/**
	 * Joins together two groups of rooms.
	 * @param a An ID of the first groop.
	 * @param b An ID of the second groop.
	 */
	void unite(int a, int b);

	/**
	 * Prints to the standard output a visual representation of the generated maze.
	 */
	void draw();
};
