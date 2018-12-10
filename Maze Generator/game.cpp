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

void getInputs(vector<int> &keys, int checkTime, sf::RenderWindow &window, vector<Square> squaresVector, maze currentMaze, sf::Font theFont);

bool checkUserInput(vector<int> keys, maze currentMaze, sf::RenderWindow &window, vector<Square> squaresVector);

const int windowSize = 600;

int main() {
	srand(time(NULL));
	//maze currentMaze;
	//currentMaze.genMaze();
	vector<int> keys;
	bool failMaze = false;
	bool genMaze = true;
	int currentWidth = 5, currentTime = 5;

	// Load font
	sf::Font theFont;
	if (!theFont.loadFromFile("arial.ttf")) {
		cout << "Error loading font. Exiting Program ... ";
		exit(-1);
	}


	sf::RenderWindow window(sf::VideoMode(windowSize + 200, windowSize), "Maze Game");
	
	
	vector<Square> squaresVector;
	
	
		while (window.isOpen() && failMaze == false && genMaze == true) // Event Loop
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			// Generate maze for round
			maze currentMaze;
			currentMaze.width = currentWidth;
			currentMaze.genMaze();

			// Create vector of squares that matches dimensions of maze


			int sideLength = sqrt(currentMaze.dimensions);
			for (int i = 0; i < sideLength; i++) {
				for (int j = 0; j < sideLength; j++) {



					sf::Color tempColor;
					switch (currentMaze.getSquareValue(j + i * sideLength)) {
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

					squaresVector.push_back(Square(windowSize / sideLength - 4, (windowSize / sideLength) * j + 4, (windowSize / sideLength) * i + 4, tempColor));
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

			getInputs(keys, currentTime, window, squaresVector, currentMaze, theFont);

			if (checkUserInput(keys, currentMaze, window, squaresVector)) {
				// Clear previous vectors 
				keys.clear();
				squaresVector.clear();
			}
			else {
				failMaze = true;
			}
			currentWidth += 2;
			currentTime += 1 + (5 * (5.0 / currentWidth));


		} // End Event loop

		// Second loop for reading mazes from file
		int mazeLevel = 1;
		while (window.isOpen() && failMaze == false && genMaze == false) // Event Loop
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			// Generate maze for round
			maze currentMaze(mazeLevel);
			
			

			// Create vector of squares that matches dimensions of maze


			int sideLength = sqrt(currentMaze.dimensions);
			for (int i = 0; i < sideLength; i++) {
				for (int j = 0; j < sideLength; j++) {



					sf::Color tempColor;
					switch (currentMaze.getSquareValue(j + i * sideLength)) {
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

					squaresVector.push_back(Square(windowSize / sideLength - 4, (windowSize / sideLength) * j + 2, (windowSize / sideLength) * i + 2, tempColor));
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
			
			getInputs(keys, 20, window, squaresVector, currentMaze, theFont);
			if (checkUserInput(keys, currentMaze, window, squaresVector)) {
				// Clear previous vectors 
				keys.clear();
				squaresVector.clear();
			}
			else {
				failMaze = true;
			}

			mazeLevel++;


		} // End Event loop


	
	
}

// Function Definitions
void getInputs(vector<int> &keys, int checkTime, sf::RenderWindow &window, vector<Square> squaresVector, maze currentMaze, sf::Font theFont) {
	time_t startTime, endTime, currentTime;
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

		// Display current window
		window.clear();
		// Draw backgroud square
		sf::Color grey(75, 75, 75);
		Square backgroundSquare = Square(windowSize, 0, 0, grey);
		window.draw(backgroundSquare.getTheSquare());
		// Draw squares to screen
		for (int i = 0; i < currentMaze.dimensions; i++) {
			window.draw(squaresVector[i].getTheSquare());
		}

		// Add timer to window

		string strCurrentTime = to_string(checkTime - int(time(&currentTime) - startTime));
		sf::Text timerText(strCurrentTime, theFont, 50);
		timerText.setPosition(windowSize + 75, 5);
		window.draw(timerText);
		window.display();
	}
}

bool checkUserInput(vector<int> keys, maze currentMaze, sf::RenderWindow &window, vector<Square> squaresVector) {

	// Add graphics support

	int start = currentMaze.start;
	int finish = currentMaze.finish;
	int player = start;
	bool success = false;
	int mazeWidth = sqrt(currentMaze.dimensions);

	for (int i = 0; i < keys.size(); i++) {

		// Move player given direction
		int move = keys.at(i);
		switch (move) {
		case 1: // Move left
			player--; 
			break;
		case 2: // Move up
			player -= mazeWidth; 
			break;
		case 3: // Move right
			player++; 
			break;
		case 4: // Move down
			player += mazeWidth;
			break;
		}

		// Store previous color and set current player square to blue
		sf::Color tempColor = squaresVector[player].getColor();
		int prevPlayer = player;
		squaresVector[player].setTheColor(sf::Color::Blue);

		// Update maze graphics
		window.clear();
		// Draw backgroud square
		sf::Color grey(75, 75, 75);
		Square backgroundSquare = Square(windowSize, 0, 0, grey);
		window.draw(backgroundSquare.getTheSquare());

		// Draw squares to screen
		for (int i = 0; i < currentMaze.dimensions; i++) {
			window.draw(squaresVector[i].getTheSquare());
		}
		window.display();

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

		squaresVector[prevPlayer].setTheColor(tempColor);

		// Wait so it is readable
		sleep(400);

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

