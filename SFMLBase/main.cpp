// SFMLBase - by Paul Hindt
// 06/09/2015

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "main.h"
#include "entity.h"

static sf::Vector2i g_MousePos;
sf::CircleShape shape;
sf::Font myFont;		
sf::Text myText;
sf::Text fpsText;
std::string mousePosString;
std::string fpsString;
sf::Drawable *g_RenderObjects[MAX_DRAWABLES];
int frameCount = 0;
float fps = 0.f;

Entity *g_edict[MAX_ENTITIES];

int main(int argc, char *argv[])
{
	int drawableCount = 0;
	int entityCount = 0;

	// create a new SFML window context
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFMLBase", sf::Style::Close);
	window.setMouseCursorVisible(false);

	// create an SFML circle shape, set it's position and color	
	shape.setRadius(10.f);
	shape.setPosition(160, 120);
	shape.setFillColor(sf::Color::Green);
		
	g_RenderObjects[drawableCount] = &shape;
	++drawableCount;

	// Load a font...
	if (!myFont.loadFromFile("C:\\Windows\\Fonts\\SourceCodePro-regular.ttf")) {
		std::cout << "Error loading font!" << std::endl;
		return -1;
	}
	
	std::cout << "Loaded font: " << myFont.getInfo().family << std::endl;

	// set parameters of my text object
	myText.setFont(myFont);						// font which we loaded previously
	myText.setCharacterSize(15);				// font size
	myText.setStyle(sf::Text::Regular);			// font style
	myText.setColor(sf::Color::White);			// font color
	myText.setPosition(0, 0);					// position in the window

	fpsText.setFont(myFont);
	fpsText.setCharacterSize(10);
	fpsText.setStyle(sf::Text::Regular);
	fpsText.setColor(sf::Color::White);
	fpsText.setPosition(400, 0);

	g_RenderObjects[drawableCount] = &myText;
	drawableCount++;
	g_RenderObjects[drawableCount] = &fpsText;
	drawableCount++;
	
	sf::Clock gameTimer;

	// SFML main window loop
	while (window.isOpen()) {
		sf::Clock frameTimer;
		sf::Event evt;
		// SFML event loop
		while (window.pollEvent(evt)) {
			switch (evt.type) {

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
			{
				sf::Vector2f circlePos(0.f, 0.f);
				// todo(paul): find out why SFML is getting mouse position in absolute coordinates, not window coords
				g_MousePos = sf::Mouse::getPosition(window);
				circlePos.x = g_MousePos.x - shape.getRadius();
				circlePos.y = g_MousePos.y - shape.getRadius();
				// construct a string from the mouse position values, set SFML text value to the string
				mousePosString = "X: " + std::to_string(g_MousePos.x) + ", Y: " + std::to_string(g_MousePos.y);
				myText.setString(mousePosString);
				shape.setPosition(circlePos);
				break;
			}

			case::sf::Event::MouseButtonPressed:
				if (evt.mouseButton.button == sf::Mouse::Button::Left) {					
					Entity *e = new Entity();
					e->SetSize(sf::Vector2f(10.f, 10.f));
					e->SetPosition(static_cast<sf::Vector2f>(sf::Vector2f(g_MousePos)));
					g_edict[entityCount] = e;
					++entityCount;
				}
				break;
			
			case sf::Event::KeyPressed:			
				if (evt.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				break;			
			}
		}		
		
		// clear the window contents
		window.clear();

		// render the pre-defined drawable objects
		for (int i = 0; i < drawableCount; i++) {
			if (g_RenderObjects[i] != NULL) {
				window.draw(*g_RenderObjects[i]);
			}
		}

		// render the entities created by the user
		for (int j = 0; j < MAX_ENTITIES; j++) {
			if (g_edict[j] != NULL) {
				window.draw(*g_edict[j]->m_EntityRect);
			}
		}
		// if we create too many entities, overwrite the first entity
		if (entityCount == MAX_ENTITIES)
		{
			entityCount = 0;
		}

		// blit everything to the window
		window.display();

		// if duration of frame doesn't hit the targeted time (1 / MAX_FPS), round it up		
		float ms = (float)(frameTimer.getElapsedTime().asSeconds() / 1000.f);		
		while (ms < deltaTime) {
			ms += 0.0001;
		}			

		if (ms * 1000.0f > 1.0f) {
			fps = 1.f / (float)(ms / (float)frameCount);
			frameCount = 0;
		}
		++frameCount;
		fpsString = "FPS: " + std::to_string(fps);
		fpsText.setString(fpsString);		
	}

	return 0;
}