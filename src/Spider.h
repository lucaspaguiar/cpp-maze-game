#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Player.h"
#include "TileSet.h"
#include "Wall.h"

class Spider :
	public Enemy
{
public:
	Spider(sf::Vector2f pos, sf::Vector2f size, TileSet *t, float chase, float patrol, float sight, float health, float damage, float iddle_time);
	virtual ~Spider();

	virtual void Update(float delta);
	virtual void OnCollision();

protected:
	void SetupAnimation(float delta);
	void SetAIState(float delta);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};