#include "Trap.h"

Trap::Trap(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t, float damaage)
	: GameEntity(pos, size)
	, m_gid(id)
	, m_fired_gid(257)
	, m_tileSet(t)
	, m_damage(damaage)
	, m_fired(false)
{
}

Trap::~Trap()
{
}

void Trap::TrapCollisionResolution(Player *p)
{
	if (!m_fired)
	{
		if (GetBoundingBox().intersects(p->GetBoundingBox()))
		{
			//Attack player
			p->TakeDamage(m_damage);
		
			//Set Tile to Fired
			m_gid = m_fired_gid;

			m_fired = true;
		}
	}
}

void Trap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_gid > 0)
	{
		sf::Sprite &s = m_tileSet->getSprite(m_gid);
		s.setPosition(m_position.x, m_position.y);
		target.draw(s, states);
	}	
}