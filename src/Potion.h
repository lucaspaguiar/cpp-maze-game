#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"

class Potion :
	public GameEntity
{
public:
	Potion(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t, float restore_health);
	virtual ~Potion();

	bool isConsumed() { return m_isConsumed; }	
	float RestoreHealth();

private:
	TileSet *m_tileSet;
	unsigned int m_gid;
	bool m_isConsumed;
	float m_restore_health;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

