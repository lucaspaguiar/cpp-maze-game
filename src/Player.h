#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "TileSet.h"
#include "Chest.h"
#include "Key.h"
#include "Potion.h"
#include "Door.h"

class Player :
	public GameEntity
{
public:
	Player(sf::Vector2f pos, sf::Vector2f size, float speed, float health, TileSet *t);
	virtual ~Player();

	void Move(float delta);
	void TakeDamage(float d) { m_health -= d;  }
	void SetTileSet(TileSet *t) { m_tileSet = t; }	

	void PlayerBoxesCollisionResolution(Chest &chest);
	void PlayerPotionCollisionResolution(Potion &potion);
	void PlayerKeyCollisionResolution(Key &key);
	void PlayerDoorCollisionResolution(Door &door);	

	int GetHealth() { return (int) m_health;  }
	int GetKey() { return m_keys;  }

protected:
	unsigned int m_keys
		, m_gid
		, m_north_gid = 73
		, m_south_gid = 13
		, m_east_gid = 53
		, m_west_gid = 33;
	

	TileSet *m_tileSet;
	
	float m_speed
		, m_health;

	void SetupAnimation(float delta);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;	
};

