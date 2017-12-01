#include "Key.h"

Key::Key(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t)
	: GameEntity(pos, size)
	, m_gid(id)
	, m_tileSet(t)
	, m_isPickedUp(false)
{
}


Key::~Key()
{
}

unsigned int Key::PickUpKey()
{
	if (!m_isPickedUp)
	{
		m_isPickedUp = true;

		return 1;
	}
	else
	{
		return 0;
	}
}

void Key::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_gid > 0)
	{
		sf::Sprite &s = m_tileSet->getSprite(m_gid);
		s.setPosition(m_position.x, m_position.y);
		target.draw(s, states);
	}
}