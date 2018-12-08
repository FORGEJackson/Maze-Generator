#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <fstream>

#include "Cell.h"

using namespace std;

const int WIDTH = 11;

class maze {
private:
	vector<int> layout;
	// EXAMPLE MAZE: 0 = Wall, 1 = Path, 2 = Start, 3 = End
	/*  0. 1. 2. 3. 4. 5. 6. 7. 8. 9.
	00. 0  0  0  0  0  0  0  0  0  0
	10. 0  0  0  0  0  0  0  0  0  0
	20. 0  0  0  0  0  0  0  0  0  0
	30. 0  0  0  0  0  1  1  1  1  3
	40. 0  1  1  1  0  1  0  0  0  0
	50. 0  1  0  1  0  1  0  0  0  0
	60. 0  1  0  1  0  1  0  0  0  0
	70. 0  1  0  1  1  1  0  0  0  0
	80. 2  1  0  0  0  0  0  0  0  0
	90. 0  0  0  0  0  0  0  0  0  0

	*/

	cell grid[WIDTH][WIDTH];
	vector<cell> walls;
public:
	int start, finish, dimensions;

	/* Test constructor
	maze() {

		dimensions = 100;

		int tempLayout[100] = {
			 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,  1,  1,  1,  1,  3,
			 0,  1,  1,  1,  0,  1,  0,  0,  0,  0,
			 0,  1,  0,  1,  0,  1,  0,  0,  0,  0,
			 0,  1,  0,  1,  0,  1,  0,  0,  0,  0,
			 0,  1,  0,  1,  1,  1,  0,  0,  0,  0,
			 2,  1,  0,  0,  0,  0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };

		for (int i = 0; i < dimensions; i++) {

			layout.push_back(tempLayout[i]);

			if (layout.at(i) == 2) {
				start = i;
			}
			if (layout.at(i) == 3) {
				finish = i;
			}
		}

	} // End test constructor */

	maze() {	
		for (int j = 0; j < WIDTH; j++) {		//Generate each cell as a wall
			for (int i = 0; i < WIDTH; i++) {
				grid[i][j].wall = true;
				grid[i][j].xPos = i;
				grid[i][j].yPos = j;
			}
		}

		for (int j = 1; j < WIDTH; j += 2) {	//Generate a grid of valid spots
			for (int i = 1; i < WIDTH; i += 2) {
				grid[i][j].wall = false;
			}
		}
	}

	// Read maze from file as constructor
	maze(int mazeInFile) {

		// Open file stream
		ifstream fileStream;
		fileStream.open("mazes.txt");

		// Find correct maze in file
		char fileValue;
		int fileMazeLevel, fileDimensions;
		while (true) {

			fileStream >> fileValue;
			if (fileValue == 'M') {
				fileStream >> fileMazeLevel;
				if (fileMazeLevel == mazeInFile) {
					fileStream >> dimensions;
					break;
				}
			}

		}
		// Set up maze once found on file
		int fileMaze;
		for (int i = 0; i < dimensions; i++) {

			fileStream >> fileMaze;
			layout.push_back(fileMaze);
			if (layout.at(i) == 2) {
				start = i;
			}
			if (layout.at(i) == 3) {
				finish = i;
			}
		}

		// Close file stream
		fileStream.close();
	} // End file constructor





	// Methods
	int getSquareValue(int check) { return layout[check]; }

	void printMaze() {
		for (int j = 0; j < WIDTH; j++) {
			for (int i = 0; i < WIDTH; i++) {
				if (grid[i][j].wall) {
					cout << (char)219;
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	void genMaze() {
		/*
		1. Pick a cell, mark visited, add walls to stack

		2. While walls are in the stack
			1. Pick a random wall from the list, if only one cell has been visited then
				1. Make the wall into a passage			-
				2. Mark the unvisited cell as visited	-
				3. Add it's walls to the stack			-
			2. Remove the current wall from the stack	-
		*/

		int xPos = ((rand() % (WIDTH / 2)) * 2) + 1;
		int yPos = ((rand() % (WIDTH / 2)) * 2) + 1;

		grid[xPos][yPos].visited = true;

		//cout << xPos << " " << yPos << endl;

		walls.push_back(grid[xPos - 1][yPos]);
		walls.push_back(grid[xPos + 1][yPos]);
		walls.push_back(grid[xPos][yPos - 1]);
		walls.push_back(grid[xPos][yPos + 1]);

		while (!walls.empty()) {

			int vecIndex = rand() % walls.size();
			cell current = walls[vecIndex];
			walls.erase(walls.begin() + vecIndex);

			if (current.xPos != 0 && current.xPos != WIDTH - 1 && current.yPos != 0 && current.yPos != WIDTH - 1) {
				if (grid[current.xPos][current.yPos - 1].wall) { //Tests if wall is vertical
					if (!grid[current.xPos - 1][current.yPos].visited || !grid[current.xPos + 1][current.yPos].visited) {
						if (!grid[current.xPos - 1][current.yPos].visited) {
							walls.push_back(grid[current.xPos - 2][current.yPos]);
							//walls.push(grid[current.xPos][current.yPos]);	//Remove
							walls.push_back(grid[current.xPos - 1][current.yPos - 1]);
							walls.push_back(grid[current.xPos - 1][current.yPos + 1]);
						}
						if (!grid[current.xPos + 1][current.yPos].visited) {
							//walls.push(grid[current.xPos][current.yPos]);	//Remove
							walls.push_back(grid[current.xPos + 2][current.yPos]);
							walls.push_back(grid[current.xPos + 1][current.yPos - 1]);
							walls.push_back(grid[current.xPos + 1][current.yPos + 1]);
						}

						grid[current.xPos - 1][current.yPos].visited = true;
						grid[current.xPos + 1][current.yPos].visited = true;
						grid[current.xPos][current.yPos].wall = false;
					}
				}
				else {
					if (!grid[current.xPos][current.yPos - 1].visited || !grid[current.xPos][current.yPos + 1].visited) {
						if (!grid[current.xPos][current.yPos - 1].visited) {
							walls.push_back(grid[current.xPos - 1][current.yPos - 1]);
							walls.push_back(grid[current.xPos + 1][current.yPos - 1]);
							walls.push_back(grid[current.xPos][current.yPos - 2]);
							//walls.push(grid[current.xPos][current.yPos]);	//Remove
						}
						if (!grid[current.xPos][current.yPos + 1].visited) {
							walls.push_back(grid[current.xPos - 1][current.yPos + 1]);
							walls.push_back(grid[current.xPos + 1][current.yPos + 1]);
							//walls.push(grid[current.xPos][current.yPos]);	//Remove
							walls.push_back(grid[current.xPos][current.yPos + 2]);
						}

						grid[current.xPos][current.yPos - 1].visited = true;
						grid[current.xPos][current.yPos + 1].visited = true;
						grid[current.xPos][current.yPos].wall = false;
					}
				}
			}
			/*
			cout << current.xPos << " " << current.yPos << endl << endl;

			//cout << "Wall\n";

			for (int i = 0; i < walls.size(); i++) {
				cout << walls[i].xPos << " " << walls[i].yPos << endl;
			}

			printMaze();
			cout << endl;
			*/
		}
	}
};





#endif