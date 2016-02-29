#pragma once

#include <SFML/Graphics.hpp>

#define MAX_ENTITIES 512

enum EntityTypes {
	NO_TYPE = 0,
	DEFAULT = 1,
	PLAYER = 2,
	BULLET = 3,
	ENEMY = 4
};

class Entity {

public:
	Entity();
	~Entity();

	void Render(float dt);

	void SetType(EntityTypes type);
	void SetRenderable(sf::RectangleShape *rect);

	void SetPosition(sf::Vector2f pos);
	void SetVelocity(sf::Vector2f vel);

	sf::Drawable *GetRenderable();
	EntityTypes GetType();	

private:
	EntityTypes m_Type;
	sf::Vector2f m_RenderSize, m_Position, m_Velocity;	
	sf::RectangleShape *m_EntityRect;
};

void Init_Entities();
int Create_Entity(sf::Vector2f pos, sf::Vector2f vel);
void Render_Entities(sf::RenderWindow *wind, float dt);