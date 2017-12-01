#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "TileSet.h"
#include "GameEntity.h"

class Door :
	public GameEntity
{
public:
	Door(sf::Vector2f pos, sf::Vector2f size, unsigned int id, TileSet *t);
	virtual ~Door();

	bool isOpened() { return opened; }
	void SetOpen() { m_gid = m_opened_gid;  opened = true; }	

private:
	TileSet *m_tileSet;
	unsigned int m_gid
		, m_opened_gid;
	bool opened;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

