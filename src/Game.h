#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <map>

#include "Stair.h"
#include "Door.h"
#include "Wall.h"
#include "Potion.h"
#include "Trap.h"
#include "Background.h"
#include "TileSet.h"
#include "Player.h"
#include "Spider.h"
#include "Bat.h"
#include "Key.h"

class Game :
	public sf::Drawable
{
public:
	Game();
	virtual ~Game();

	bool Init(std::string file);
	void Update(float delta);
	void Shutdown();
	void Reset();

	void IncreaseDifficultyModifier() { m_difficulty_modifier += 0.10f; }
	float GetDifficultyModifier() { return m_difficulty_modifier;  }


	bool isGameOver() { return m_game_over; }
	bool loadNextLevel() { return m_load_next_level; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	TileSet *m_tileset;
	Player *m_player;
	sf::Font m_font;

	std::vector<Wall> m_walls;
	std::vector<Door> m_doors;
	std::vector<Background> m_background;
	std::vector<sf::Vector2f> m_spider_spawn_point;
	std::vector<sf::Vector2f> m_bat_spawn_point;
	sf::Vector2f m_player_spawn;
	std::vector<Spider> m_spiders;
	std::vector<Bat> m_bats;	
	std::vector<Stair> m_stair;
	std::vector<Trap> m_traps;
	std::vector<Potion> m_potions;
	std::vector<Key> m_keys;
	
	bool m_game_over;
	bool m_load_next_level;
	float m_difficulty_modifier;

	float const PLAYER_HEALTH = 100.0f;
	float const PLAYER_SPEED = 100.0f;
	float const ENEMY_HEALTH = 100.0f;
	float const ENEMY_SPEED_CHASE = 100.0f;
	float const ENEMY_SPEED_PATROL = 50.0f;
	float const ENEMY_DAMAGE = 40.0f;
	float const ENEMY_SIGHT_RANGE = 150.0f;
	float const ENEMY_WAIT_TIME = 1.0f;
	float const TRAP_DAMAGE = 15.0f;

	int m_width, 
		m_height, 
		m_tileWidth, 
		m_tileHeight;

	bool loadFromFile(std::string file);
	void loadLayerFromXML(tinyxml2::XMLElement *el, const char *value);

	bool CollisionResolution(GameEntity *g, sf::FloatRect boundig_box);
};