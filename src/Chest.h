#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"

class Chest :
	public GameEntity
{
public:
	Chest(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t);
	virtual ~Chest();

private:
	TileSet *m_tileSet;
	unsigned int m_gid;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

