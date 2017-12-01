#include "Player.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size, float speed, float health, TileSet *t)
	: GameEntity(pos, size)
	, m_speed(speed)
	, m_tileSet(t)
	, m_gid(13)
	, m_keys(0)
	, m_health(health)
{
}

Player::~Player()
{
}

void Player::Move(float delta) 
{
	m_position += m_direction * m_speed * delta;
}

void Player::SetupAnimation(float delta)
{
	switch (m_direction_enum)
	{
	case Player::NORTH:
		m_gid = m_north_gid;		
		break;
	case Player::SOUTH:
		m_gid = m_south_gid;		
		break;
	case Player::EAST:
		m_gid = m_east_gid;		
		break;
	case Player::WEST:
		m_gid = m_west_gid;		
		break;
	}
}

void Player::PlayerDoorCollisionResolution(Door &door)
{
	if (!door.isOpened())
	{
		if (m_keys > 0)
		{
			m_keys--;
			door.SetOpen();
		}
	}	
}

void Player::PlayerPotionCollisionResolution(Potion &potion)
{
	if (GetBoundingBox().intersects(potion.GetBoundingBox()))
	{
		if (m_health < 100.0f)
		{
			m_health += potion.RestoreHealth();
			
			if (m_health > 100.0f) m_health = 100.0f;
		}
	}
}

void Player::PlayerKeyCollisionResolution(Key &key)
{
	if (GetBoundingBox().intersects(key.GetBoundingBox()))
	{
		m_keys += key.PickUpKey();
	}
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
	sf::Sprite &s = m_tileSet->getSprite(m_gid);
	s.setPosition(m_position.x, m_position.y);
	target.draw(s, states);
}