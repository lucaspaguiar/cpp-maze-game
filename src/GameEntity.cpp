#include "GameEntity.h"

GameEntity::GameEntity(sf::Vector2f pos, sf::Vector2f size)
	: m_position(pos), m_size(size)
{
}


GameEntity::~GameEntity()
{
}

void GameEntity::SetDirection(GameEntity::Direction d)
{
	sf::Vector2f newDir;

	switch (d)
	{
	case GameEntity::NORTH:		
		newDir = sf::Vector2f(0.0f, -1.0f);
		break;
	case GameEntity::SOUTH:		
		newDir = sf::Vector2f(0.0f, 1.0f);
		break;
	case GameEntity::EAST:		
		newDir = sf::Vector2f(1.0f, 0.0f);
		break;
	case GameEntity::WEST:		
		newDir = sf::Vector2f(-1.0f, 0.0f);
		break;
	}

	m_direction_enum = d;
	m_direction = newDir;
}

void GameEntity::SetDirection(int d)
{
	switch (d)
	{
	case 0:
		SetDirection(GameEntity::Direction::NORTH);
		break;
	case 1:
		SetDirection(GameEntity::Direction::SOUTH);
		break;
	case 2:
		SetDirection(GameEntity::Direction::EAST);
		break;
	case 3:
		SetDirection(GameEntity::Direction::WEST);
		break;
	}
}
