#include "Spider.h"
#include <iostream>

Spider::Spider(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time)
	: Enemy(pos, size, t, chase, patrol, sight, health, damage, iddle_time)
{
	//Init GIDs
	m_north_gid = 158;
	m_south_gid = 99;
	m_east_gid = 139;
	m_west_gid = 119;
	m_gid = m_south_gid;
}

Spider::~Spider()
{
}

void Spider::Update(float delta)
{	
	SetAIState(delta);

	switch (m_AI_state)
	{
	case Spider::IDLE:
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
	case Spider::PATROL:
		m_speed = m_patrol_speed;
		break;
	case Spider::ATTACK:
		m_speed = m_chase_speed;
		break;
	case Spider::DIED:
		break;
	}
	
	m_position += m_direction * m_speed * delta;	
}

void Spider::OnCollision()
{
	m_AI_state = Enemy::IDLE;
}

void Spider::SetAIState(float delta)
{
	if (m_player_in_sight)
	{
		m_AI_state = Spider::IDLE;
	}
}


void Spider::SetupAnimation(float delta)
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

void Spider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_show_sight)
	{
		sf::Vector2f pos;
		pos.x = m_position.x + (m_size.x / 2);
		pos.y = m_position.y + (m_size.y / 2);
		sf::Vector2f siz(m_range_sight, 1);

		switch (m_direction_enum)
		{
		case Spider::NORTH:
			siz = sf::Vector2f(1, m_range_sight);
			pos.y -= siz.y;
			break;
		case Spider::SOUTH:
			siz = sf::Vector2f(1, m_range_sight);
			break;	
		case Spider::WEST:
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