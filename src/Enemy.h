#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Player.h"
#include "TileSet.h"
#include "Wall.h"

class Enemy :
	public GameEntity
{
public:
	Enemy(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time);
	
	virtual ~Enemy();

	enum State
	{
		IDLE,
		PATROL,
		ATTACK,
		DIED
	};

	virtual void Update(float delta) = 0;
	virtual void OnCollision() = 0;

	void EnemyCollisionResolution(Player *p);
	void EnemySight(Player *p, std::vector<Wall> &obst);
	void TakeDamage(float d) { m_health -= d; }
	void SetShowSight() { m_show_sight = !m_show_sight; }
	bool isDead() { return (m_health <= 0.0f); }

protected:
	unsigned int  m_gid
		, m_north_gid
		, m_south_gid
		, m_east_gid
		, m_west_gid;

	sf::Vector2f m_previous_direction;
	TileSet *m_tileSet;

	float m_speed
		, m_chase_speed
		, m_patrol_speed
		, m_range_sight
		, m_health
		, m_damage
		, m_idle_time
		, m_idle_timer;

	bool m_player_in_sight;
	bool m_show_sight;

	State m_AI_state;

	virtual void SetupAnimation(float delta) = 0;
	virtual void SetAIState(float delta) = 0;

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

