#include "Door.h"

Door::Door(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t)
	: GameEntity(pos, size)
	, m_gid(id)
	, m_opened_gid(229)
	, m_tileSet(t)
	, opened(false)
{
}

Door::~Door()
{
}


void Door::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_gid > 0)
	{
		sf::Sprite &s = m_tileSet->getSprite(m_gid);
		s.setPosition(m_position.x, m_position.y);
		target.draw(s, states);
	}
}