#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity();
	~Entity();

	void SetSize(sf::Vector2f size);
	void SetPosition(sf::Vector2f pos);
	void SetVelocity(sf::Vector2f vel);

	sf::RectangleShape *m_EntityRect;

private:
	sf::Vector2f m_Size;
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	
};