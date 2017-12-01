#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"

class Key :
	public GameEntity
{
public:
	Key(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t);
	virtual ~Key();

	bool isPickedUp() { return m_isPickedUp; }
	unsigned int PickUpKey();

private:
	TileSet *m_tileSet;
	unsigned int m_gid;
	bool m_isPickedUp;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

