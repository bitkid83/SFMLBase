#include "entity.h"

Entity::Entity()
: 
m_Position(0.f, 0.f),
m_Velocity(0.f, 0.f),
m_EntityRect(new sf::RectangleShape(sf::Vector2f(0.f, 0.f)))
{ 
}

Entity::~Entity()
{
	delete m_EntityRect;
}

void Entity::SetSize(sf::Vector2f size)
{
	this->m_Size = size;
	m_EntityRect->setSize(this->m_Size);
}

void Entity::SetPosition(sf::Vector2f pos)
{
	this->m_Position = pos;
	m_EntityRect->setPosition(this->m_Position);
}

void Entity::SetVelocity(sf::Vector2f vel)
{
	this->m_Velocity = vel;
}