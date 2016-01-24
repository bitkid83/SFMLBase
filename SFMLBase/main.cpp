// SFMLBase - by Paul Hindt
// 06/09/2015

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

sf::Vector2i mousePos;	// for storing mouse position x & y
sf::Font myFont;		// for loading a font file from disk
sf::Text myText;		// this is our actual text object where we set the string, style, size, etc.
std::string mousePosString;

int main(int argc, char *argv[])
{
	// create a new SFML window context
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFMLBase");

	// create an SFML circle shape, set it's position and color
	sf::CircleShape shape(150.f);
	shape.setPosition(160, 120);	
	shape.setFillColor(sf::Color::Green);
	
	// Load a font...
	if (!myFont.loadFromFile("C:\\Windows\\Fonts\\tahoma.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}
	else{
		std::cout << "Loaded font: " << myFont.getInfo().family << std::endl;
	}

	// set parameters of my text object
	myText.setFont(myFont);						// font which we loaded previously
	myText.setCharacterSize(24);				// font size
	myText.setStyle(sf::Text::Regular);			// font style
	myText.setColor(sf::Color::Red);			// font color
	myText.setPosition(0, 0);					// position in the window
	//myText.setString("Hello world!");			// the string! (I over-ride this later with mouse position text)

	// SFML main window loop
	while (window.isOpen()) {
		sf::Event evt;
		// SFML event loop
		while (window.pollEvent(evt)) {
			switch (evt.type) {

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:				
				// todo(paul): find out why SFML is getting mouse position in absolute coordinates, not window coords
				mousePos = sf::Mouse::getPosition(window);
				mousePosString = "X: " + std::to_string(mousePos.x) + ", Y: " + std::to_string(mousePos.y);
				// construct a string from the mouse position values, set SFML text value to the string
				myText.setString(mousePosString);
				//std::cout << mousePos.x << "," << mousePos.y << std::endl;
				break;

			case sf::Event::KeyPressed:
				if (evt.key.code == sf::Keyboard::Space) {
					shape.setPosition(static_cast<sf::Vector2f>(mousePos));
				}
				break;
			}
		}

		// clear the window contents
		window.clear();

		// todo(paulh): SFML has a base class called "drawable"
		// it looks like "shape" and "text" inherit from that class
		// we could set up a loop to iterate over an array of drawables instead of doing it one by one
		window.draw(shape);
		window.draw(myText);

		// blit everything to the window
		window.display();
	}

	return 0;
}