#include "Potion.h"

Potion::Potion(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t, float restore_health)
	: GameEntity(pos, size)
	, m_gid(id)
	, m_tileSet(t)
	, m_isConsumed(false)
	, m_restore_health(restore_health)
{
}

Potion::~Potion()
{
}

float Potion::RestoreHealth()
{
	if (!m_isConsumed)
	{
	m_isConsumed = true;
	
	return m_restore_health;
	}
	else 
	{
		return 0.0f;
	}
}

void Potion::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_gid > 0)
	{
		sf::Sprite &s = m_tileSet->getSprite(m_gid);
		s.setPosition(m_position.x, m_position.y);
		target.draw(s, states);
	}	
}