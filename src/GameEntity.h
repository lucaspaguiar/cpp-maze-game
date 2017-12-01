#pragma once
#include <SFML\Graphics\Drawable.hpp>
class GameEntity :
	public sf::Drawable
{
public:
	GameEntity(sf::Vector2f pos, sf::Vector2f size);
	~GameEntity();

	enum Direction
	{
		NORTH,
		SOUTH,
		EAST,
		WEST
	};

	sf::FloatRect GetBoundingBox() {
		return sf::FloatRect(m_position.x, m_position.y, m_size.x, m_size.y);
	}

	void SetDirection(GameEntity::Direction d);
	void SetDirection(int d);
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetCenter() { return sf::Vector2f(m_position.x + (m_size.x / 2), m_position.y + (m_size.y / 2)); }
	sf::Vector2f GetPosition() { return m_position; }

protected:
	Direction m_direction_enum;
	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};

