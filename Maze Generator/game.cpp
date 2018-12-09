// Maze Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <string>
#include <cmath>

#include "maze.h"
#include "mazesquare.h"
using namespace std;


// Function Declarations
void sleep(unsigned milliseconds) {
	Sleep(milliseconds);
}

void getInputs(vector<int> &keys, int checkTime);

bool checkUserInput(vector<int> keys, maze currentMaze);


int main() {
	maze currentMaze;
	currentMaze.genMaze();
	
	const int windowSize = 600;
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "SFML works!");
	
	
	vector<Square> squaresVector(currentMaze.dimensions);
	
	

	while (window.isOpen()) // Event Loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		// Create vector of squares that matches dimensions of maze
		
		
		int sideLength = sqrt(currentMaze.dimensions);
		for (int i = 0; i < sideLength; i++) {
			for (int j = 0; j < sideLength; j++) {



				sf::Color tempColor;
				switch (currentMaze.getSquareValue(i+j * sideLength)) {
				case 0:
					tempColor = sf::Color::Black;
					break;
				case 1:
					tempColor = sf::Color::White;
					break;
				case 2:
					tempColor = sf::Color::Green;
					break;
				case 3:
					tempColor = sf::Color::Red;
					break;
				}

				squaresVector[i + j*sideLength] = Square(windowSize / sideLength - 4, (windowSize / sideLength) * i + 2, (windowSize / sideLength) * j + 2, tempColor);
			}
		} 
		
		
		window.clear();
		// Draw backgroud square
		sf::Color grey(75, 75, 75);
		Square backgroundSquare = Square(windowSize, 0, 0, grey);
		window.draw(backgroundSquare.getTheSquare());

		// Draw Maze squares
		for (int i = 0; i < currentMaze.dimensions; i++) {
			window.draw(squaresVector[i].getTheSquare());
		}
		
		
		
		window.display();
	}
	
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
	- Add undo on inputs????
	- Add timer to interface
* Validate user input agaisnt maze for level
	- Parse through maze to see if successful *DONE*
	- Show users attempt on graphics


*/

