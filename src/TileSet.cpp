#include "TileSet.h"
#include <iostream>

TileSet::TileSet() : m_tilewidth(0), m_tileheight(0), m_texwidth(0), m_texheight(0)
{
}


TileSet::~TileSet()
{
}

bool TileSet::loadFromXML(tinyxml2::XMLElement *el) {
	m_tilewidth = el->IntAttribute("tilewidth");
	m_tileheight = el->IntAttribute("tileheight");
	

	tinyxml2::XMLElement *imageEl = el->FirstChildElement("image");
	std::string source = imageEl->Attribute("source");
	m_texwidth = imageEl->IntAttribute("width");
	m_texheight = imageEl->IntAttribute("height");

	m_texture.loadFromFile(source);
	if (m_texture.getSize().x != m_texwidth || m_texture.getSize().y != m_texheight) {
		std::cout << "Error loading image at " << source << std::endl;
		return false;
	}

	for (int y = 0; y < m_texheight / m_tileheight; y++) {
		for (int x = 0; x < m_texwidth / m_tilewidth; x++) {
			m_sprites.push_back(sf::Sprite(m_texture, sf::IntRect(x * m_tilewidth, y * m_tileheight, m_tilewidth, m_tileheight)));
		}
	}
	return true;
}

sf::Sprite &TileSet::getSprite(unsigned int id) {
	//oh boy is this ever unsafe.
	return m_sprites[id - 1];
}