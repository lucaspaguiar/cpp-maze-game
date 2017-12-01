#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"
#include "Player.h"

class Trap :
	public GameEntity
{
public:
	Trap(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t, float damage);
	virtual ~Trap();

	void TrapCollisionResolution(Player *p);

	bool isFired() { return m_fired; }

private:
	TileSet *m_tileSet;

	float m_damage;
	bool m_fired;

	unsigned int  m_gid
				, m_fired_gid;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

