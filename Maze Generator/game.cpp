#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <string>

#include "maze.h"
#include "Cell.h"
#include "mazesquare.h"

using namespace std;


// Function Declarations
void sleep(unsigned milliseconds) {
	Sleep(milliseconds);
}

void getInputs(vector<int> &keys, int checkTime);

bool checkUserInput(vector<int> keys, maze currentMaze);


int main() {
	maze testMaze;
	testMaze.genMaze();

	for (int i = 0; i < testMaze.dimensions; i++) {
		cout << testMaze.getSquareValue(i) << " ";
		if (i % 11 == 10) {
			cout << endl;
		}
	}

	int test;
	cin >> test;
}

// Function Definitions
void getInputs(vector<int> &keys, int checkTime) {
	time_t startTime, endTime;
	time(&startTime);

	int L = 0, R = 0, U = 0, D = 0;

	while (startTime + checkTime != time(&endTime)) {
		sleep(1000 / 60); // Frames per second

		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && L < 0) {
			L = 8;
			keys.push_back(1);

		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) && U < 0) {
			U = 8;
			keys.push_back(2);
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && R < 0) {
			R = 8;
			keys.push_back(3);
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && D < 0) {
			D = 8;
			keys.push_back(4);
		}

		// Deincrement all counters
		L--; R--; U--; D--;
	}
}

bool checkUserInput(vector<int> keys, maze currentMaze) {

	// Add graphics support

	int start = currentMaze.start;
	int finish = currentMaze.finish;
	int player = start;
	bool success = false;

	for (int i = 0; i < keys.size(); i++) {

		// Move player given direction
		int move = keys.at(i);
		switch (move) {
		case 1: // Move left
			if (player % 10 != 0) { player--; }
			break;
		case 2: // Move up
			if (player - 10 > -1) { player -= 10; }
			break;
		case 3:
			if (player % 10 != 9) { player++; }
			break;
		case 4:
			if (player + 10 < 101) { player += 10; }
			break;
		}

		// Update maze graphics

		// Validate movement
		if (currentMaze.getSquareValue(player) == 0) {
			// Incorrect move 
			cout << "Incorrect Move Player = " << player << endl;
			break;
		}
		if (player == finish) {
			// Maze completion
			success = true;
			break;
		}


	} // End for loop

	// Check if user beat maze
	return success;

}


/* TO DO:

* read and initialize mazes from a file *DONE*

* Create graphics interface
  - Create maze of squares on screen
  - Add title screen or just use text based prompt?

* Generate mazes randomly or based on seed

* Get user input
	- Add all inputs to vector	*DONE*
	- Add timer to interface
* Validate user input agaisnt maze for level
	- Parse through maze to see if successful *DONE*
	- Show users attempt on graphics


*/
