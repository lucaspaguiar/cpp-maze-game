#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Player.h"
#include "TileSet.h"
#include "Wall.h"

class Bat :
	public Enemy
{
public:
	Bat(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time);
	virtual ~Bat();

	virtual void Update(float delta);
	virtual void OnCollision();

protected:
	virtual void SetupAnimation(float delta);
	virtual void SetAIState(float delta);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

