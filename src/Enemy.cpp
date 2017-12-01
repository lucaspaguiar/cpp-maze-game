#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time)
	: GameEntity(pos, size)
	, m_speed(patrol)
	, m_chase_speed(chase)
	, m_tileSet(t)
	, m_patrol_speed(patrol)
	, m_range_sight(sight)
	, m_health(health)
	, m_damage(damage)
	, m_idle_time(iddle_time)
	, m_idle_timer(0.0f)
	, m_show_sight(false)
	, m_player_in_sight(false)
{
	SetDirection(GameEntity::Direction::SOUTH);
}

Enemy::~Enemy()
{
}

void Enemy::EnemyCollisionResolution(Player *p)
{
	if (GetBoundingBox().intersects(p->GetBoundingBox()))
	{
		//Attack player
		p->TakeDamage(m_damage);

		TakeDamage(m_health);
	}
}

void Enemy::EnemySight(Player *p, std::vector<Wall> &obst)
{
	bool isPlayerInSight = false;

	sf::Vector2f pos = GetCenter();
	sf::Vector2f siz(m_range_sight, 1);

	switch (m_direction_enum)
	{
	case Enemy::NORTH:
		siz = sf::Vector2f(1, m_range_sight);
		pos.y -= siz.y;
		break;
	case Enemy::SOUTH:
		siz = sf::Vector2f(1, m_range_sight);
		break;
	case Enemy::EAST:
		break;
	case Enemy::WEST:
		pos.x -= siz.x;
		break;
	}

	sf::FloatRect line(pos, siz);
	float player_dist = 0.0f;
	std::vector<float> obj_dist;
	if (line.intersects(p->GetBoundingBox()))
	{
		//Check Dist From Enemy To Player
		switch (m_direction_enum)
		{
		case Enemy::NORTH:
			player_dist = GetBoundingBox().top - (p->GetBoundingBox().top + p->GetBoundingBox().height);
			break;
		case Enemy::SOUTH:
			player_dist = p->GetBoundingBox().top - (GetBoundingBox().top + GetBoundingBox().height);
			break;
		case Enemy::EAST:
			player_dist = p->GetBoundingBox().left - (GetBoundingBox().left + GetBoundingBox().width);
			break;
		case Enemy::WEST:
			player_dist = GetBoundingBox().left - (p->GetBoundingBox().left + p->GetBoundingBox().width);
			break;
		}

		//Check Dist From Enemy to sight obstacles
		for (int i = 0; i < obst.size(); i++)
		{
			sf::FloatRect area;
			if (line.intersects(obst[i].GetBoundingBox(), area))
			{
				//Check Dist From Enemy To Player
				switch (m_direction_enum)
				{
				case Enemy::NORTH:
					obj_dist.push_back(GetBoundingBox().top - (obst[i].GetBoundingBox().top + obst[i].GetBoundingBox().height));
					break;
				case Enemy::SOUTH:
					obj_dist.push_back(obst[i].GetBoundingBox().top - (GetBoundingBox().top + GetBoundingBox().height));
					break;
				case Enemy::EAST:
					obj_dist.push_back(obst[i].GetBoundingBox().left - (GetBoundingBox().left + GetBoundingBox().width));
					break;
				case Enemy::WEST:
					obj_dist.push_back(GetBoundingBox().left - (obst[i].GetBoundingBox().left + obst[i].GetBoundingBox().width));
					break;
				}
			}
		}

		isPlayerInSight = true;
		//Compare distances
		for (int i = 0; i < obj_dist.size(); i++)
		{
			if (obj_dist[i] < player_dist)
			{
				isPlayerInSight = false;
			}
		}
	}

	m_player_in_sight = isPlayerInSight;
}