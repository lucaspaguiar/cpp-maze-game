#pragma once

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "tinyxml2.h"

class TileSet
{
public:
	TileSet();
	virtual ~TileSet();
	bool loadFromXML(tinyxml2::XMLElement *el);
	sf::Sprite &getSprite(unsigned int id);

	sf::Vector2i getTileSize() {
		return sf::Vector2i(m_tilewidth, m_tileheight);
	}

	sf::Vector2f GetTileSize() {
		return sf::Vector2f(m_tilewidth, m_tileheight);
	}

private:
	sf::Texture m_texture;
	std::vector<sf::Sprite> m_sprites;
	int m_tilewidth, m_tileheight, m_texwidth, m_texheight;
};

