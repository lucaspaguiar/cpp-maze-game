#include "Bat.h"
#include <iostream>

Bat::Bat(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time)
	: Enemy(pos, size, t, chase, patrol, sight, health, damage, iddle_time)	
{	
	m_north_gid = 153;
	m_south_gid = 93;
	m_east_gid = 133;
	m_west_gid = 113;
	m_gid = m_south_gid;
}

Bat::~Bat()
{
}

void Bat::Update(float delta)
{
	SetAIState(delta);

	switch (m_AI_state)
	{
	case Bat::IDLE:
		m_speed = 0.0f;
		m_idle_timer += delta;

		if (m_idle_timer > m_idle_time)
		{
			m_idle_timer = 0.0f;
			m_AI_state = State::PATROL;
			m_previous_direction = m_direction;
			while (m_previous_direction == m_direction)
			{
				int r = rand() % 4;
				SetDirection(r);
			}
		}
		break;
	case Bat::PATROL:
		m_speed = m_patrol_speed;
		break;
	case Bat::ATTACK:
		m_speed = m_chase_speed;
		break;
	case Bat::DIED:
		break;
	}

	m_position += m_direction * m_speed * delta;
}

void Bat::OnCollision()
{
	m_AI_state = Enemy::IDLE;
}

void Bat::SetAIState(float delta)
{
	if (m_player_in_sight)
	{
		m_AI_state = Bat::ATTACK;
	}
}

void Bat::SetupAnimation(float delta)
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

void Bat::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_show_sight)
	{
		sf::Vector2f pos;
		pos.x = m_position.x + (m_size.x / 2);
		pos.y = m_position.y + (m_size.y / 2);
		sf::Vector2f siz(m_range_sight, 1);

		switch (m_direction_enum)
		{
		case Bat::NORTH:
			siz = sf::Vector2f(1, m_range_sight);
			pos.y -= siz.y;
			break;
		case Bat::SOUTH:
			siz = sf::Vector2f(1, m_range_sight);
			break;
		case Bat::WEST:
			pos.x -= siz.x;
			break;
		}

		sf::RectangleShape line(siz);
		line.setFillColor(sf::Color::Red);
		line.setPosition(pos);
		target.draw(line, states);
	}

	sf::Sprite &s = m_tileSet->getSprite(m_gid);
	s.setPosition(m_position.x, m_position.y);
	target.draw(s, states);
}