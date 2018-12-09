#ifndef MAZESQUARE_H
#define MAZESQUARE_H



#include <SFML/Graphics.hpp>
#include <string>

class Square {
public:
	// Default Constructor 
	Square()
	{
		size = 0;
		xPosition = 0;
		yPosition = 0;
		color = sf::Color::Black;
	}

	// Fully-qualified constructor, used to set all fields
	Square(int theSize, int theXPosition, int theYPosition,
		sf::Color setColor)
	{
		// Set the class fields
		size = theSize;
		xPosition = theXPosition;
		yPosition = theYPosition;
		
		color = setColor;
		// Use the values to set the display characteristics of theSquare
		theSquare.setSize(sf::Vector2f(theSize, theSize));
		theSquare.setPosition(theXPosition, theYPosition);   // Set the position of the square
		theSquare.setFillColor(color);
		
	}

	// Get (accessor) functions
	sf::RectangleShape getTheSquare() { return theSquare; }
	int getSize() { return size; }
	int getXPosition() { return xPosition; }
	int getYPosition() { return yPosition; }
	sf::Color& getColor() { return color; }

	// Set (mutator) functions
	void setSize(int theSize) {
		size = theSize;
		theSquare.setSize(sf::Vector2f(theSize, theSize));
	}
	void setXPosition(int theXPosition) {
		xPosition = theXPosition;
		theSquare.setPosition(theXPosition, yPosition);   // Set the position of the square
	}
	void setYPosition(int theYPosition) {
		yPosition = theYPosition;
		theSquare.setPosition(xPosition, theYPosition);   // Set the position of the square
	}
	void setTheColor(sf::Color  theColor) {
		color = theColor;
		theSquare.setFillColor(theColor);    // Also update the color on the square itself
	}

	

private:
	int size;
	int xPosition;
	int yPosition;
	sf::Color color;
	sf::RectangleShape theSquare;

}; //end class Square





#endif

