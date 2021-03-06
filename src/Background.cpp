#include "Background.h"

Background::Background(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t)
	: GameEntity(pos, size)
	, m_id(id)
	, m_tileSet(t)
{
}


Background::~Background()
{
}


void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_id > 0)
	{
		sf::Sprite &s = m_tileSet->getSprite(m_id);
		s.setPosition(m_position.x, m_position.y);
		target.draw(s, states);
	}
}