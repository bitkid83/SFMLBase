#include "entity.h"

Entity *g_edict = 0;
const sf::Vector2f g_Gravity(0.5f, 1.5f);

Entity::Entity()
: 
m_Position(0.f, 0.f),
m_Velocity(0.f, 0.f)
//m_EntityRect(new sf::RectangleShape(sf::Vector2f(0.f, 0.f)))
{
}

Entity::~Entity()
{
	//delete m_EntityRect;
}

void Entity::Render(float dt)
{
	m_Position += (g_Gravity + m_Velocity) * dt;
	m_EntityRect->setPosition(m_Position);
}

void Entity::SetType(EntityTypes type)
{
	m_Type = type;
}

void Entity::SetRenderable(sf::RectangleShape *shape)
{	
	m_EntityRect = shape;
}

void Entity::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	// m_EntityRect.setPosition(m_Position);
}

void Entity::SetVelocity(sf::Vector2f vel)
{
	m_Velocity = vel;
}

sf::Drawable *Entity::GetRenderable()
{
	return m_EntityRect;
}

EntityTypes Entity::GetType()
{
	return m_Type;
}

// Entity utility functions
void Init_Entities()
{
	int sz_ents = sizeof(Entity) * MAX_ENTITIES;
	g_edict = (Entity *)malloc(sz_ents);
	memset(g_edict, 0, sz_ents);

	sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(10.f, 10.f));
	shape->setFillColor(sf::Color::White);
	// initialize the rectangle shape that represents this entity
	for (int i = 0; i < MAX_ENTITIES; i++){
		g_edict[i].SetRenderable(shape);
	}
}

int Create_Entity(sf::Vector2f pos, sf::Vector2f vel)
{
	int entity_index = 0;	

	while (g_edict[entity_index].GetType() != NO_TYPE)
	{
		if (entity_index == MAX_ENTITIES - 1) {
			entity_index = 0;
		} 
		else
			entity_index++;
	}

	g_edict[entity_index].SetType(DEFAULT);
	g_edict[entity_index].SetPosition(pos);
	g_edict[entity_index].SetVelocity(vel);

	return 0;
}

void Render_Entities(sf::RenderWindow *wind, float dt)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		g_edict[i].Render(dt);
		if (g_edict[i].GetType() != NO_TYPE && g_edict[i].GetRenderable() != nullptr) {
			wind->draw(*g_edict[i].GetRenderable());
		}
	}
}