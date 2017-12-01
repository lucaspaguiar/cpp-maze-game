#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"

class Stair :
	public GameEntity
{
public:
	Stair(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t);
	virtual ~Stair();

private:
	TileSet *m_tileSet;
	unsigned int m_id;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

