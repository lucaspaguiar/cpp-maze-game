#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

Game::Game() :	m_width(0)
				, m_height(0)
				, m_tileWidth(0)
				, m_tileHeight(0)
				, m_tileset(NULL)
				, m_player(NULL)
				, m_difficulty_modifier(1.0f)
				, m_load_next_level(false)
				, m_game_over(false)
{
}


Game::~Game()
{	
}

bool Game::Init(std::string file)
{
	bool r = loadFromFile(file);
	
	r = r && m_font.loadFromFile("RAVIE.TTF");

	if (m_player == NULL)
	{
		m_player = new Player(m_player_spawn
							, m_tileset->GetTileSize()
							, PLAYER_SPEED
							, PLAYER_HEALTH
							, m_tileset);
	}
	else
	{
		//Reset Player Position and re-assign tileset pointer
		m_player->SetPosition(m_player_spawn);
		m_player->SetTileSet(m_tileset);
	}

	for (int i = 0; i < m_spider_spawn_point.size(); i++)
	{
		m_spiders.push_back(Spider(m_spider_spawn_point[i]
								 , m_tileset->GetTileSize()
								 , m_tileset
								 , ENEMY_SPEED_CHASE * m_difficulty_modifier
								 , ENEMY_SPEED_PATROL * m_difficulty_modifier
								 , ENEMY_SIGHT_RANGE * m_difficulty_modifier
								 , ENEMY_HEALTH
								 , ENEMY_DAMAGE * m_difficulty_modifier
								 , ENEMY_WAIT_TIME / m_difficulty_modifier));
	}

	for (int i = 0; i < m_bat_spawn_point.size(); i++)
	{
		m_bats.push_back(Bat(m_bat_spawn_point[i]
						   , m_tileset->GetTileSize()
						   , m_tileset
						   , ENEMY_SPEED_CHASE * m_difficulty_modifier
						   , ENEMY_SPEED_PATROL * m_difficulty_modifier
						   , ENEMY_SIGHT_RANGE * m_difficulty_modifier
						   , ENEMY_HEALTH
						   , ENEMY_DAMAGE * m_difficulty_modifier
						   , ENEMY_WAIT_TIME / m_difficulty_modifier));
	}

	return r;
}

void Game::Shutdown()
{
	Reset();

	free(m_player);
	m_player = NULL;

	m_difficulty_modifier = 1.0f;
}

void Game::Reset()
{
	free(m_tileset);

	m_walls.clear();
	m_doors.clear();
	m_background.clear();
	m_spider_spawn_point.clear();
	m_bat_spawn_point.clear();	
	m_spiders.clear();
	m_bats.clear();
	m_stair.clear();
	m_traps.clear();
	m_potions.clear();
	m_keys.clear();

	m_game_over = false;
	m_load_next_level = false;
}

void Game::Update(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player->SetDirection(Player::Direction::NORTH);
		m_player->Move(delta);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player->SetDirection(Player::Direction::SOUTH);
		m_player->Move(delta);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player->SetDirection(Player::Direction::EAST);
		m_player->Move(delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player->SetDirection(Player::Direction::WEST);
		m_player->Move(delta);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{ 
		for (int i = 0; i < m_spiders.size(); i++)
		{
			m_spiders[i].SetShowSight();
		}

		for (int i = 0; i < m_bats.size(); i++)
		{
			m_bats[i].SetShowSight();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_load_next_level = true;
	}

	//Check for dead enemies
	std::vector<int> toEraseSpider;

	for (int i = 0; i < m_spiders.size(); i++)
	{
		if (m_spiders[i].isDead())
		{
			toEraseSpider.push_back(i);
		}		
	}

	for (int i = 0; i < toEraseSpider.size(); i++)
	{
		m_spiders.erase(m_spiders.begin() + toEraseSpider[i]);
	}

	//Check for dead enemies
	std::vector<int> toEraseBats;

	for (int i = 0; i < m_bats.size(); i++)
	{
		if (m_bats[i].isDead())
		{
			toEraseBats.push_back(i);
		}
	}

	for (int i = 0; i < toEraseBats.size(); i++)
	{
		m_bats.erase(m_bats.begin() + toEraseBats[i]);
	}

	//Check for consumed potions
	std::vector<int> toErasePotions;

	for (int i = 0; i < m_potions.size(); i++)
	{
		if (m_potions[i].isConsumed())
		{
			toErasePotions.push_back(i);
		}
	}

	for (int i = 0; i < toErasePotions.size(); i++)
	{
		m_potions.erase(m_potions.begin() + toErasePotions[i]);
	}

	//Check for consumed potions
	std::vector<int> toEraseKeys;

	for (int i = 0; i < m_keys.size(); i++)
	{
		if (m_keys[i].isPickedUp())
		{
			toEraseKeys.push_back(i);
		}
	}

	for (int i = 0; i < toEraseKeys.size(); i++)
	{
		m_keys.erase(m_keys.begin() + toEraseKeys[i]);
	}

	//Update Spider
	for (int i = 0; i < m_spiders.size(); i++)
	{
		m_spiders[i].Update(delta);
		m_spiders[i].EnemySight(m_player, m_walls);
	}

	//Update Bat
	for (int i = 0; i < m_bats.size(); i++)
	{
		m_bats[i].Update(delta);
		m_bats[i].EnemySight(m_player, m_walls);
	}

	//#######################################################################################

	//Collision Check with Wall
	for (int i = 0; i < m_walls.size(); i++)
	{
		CollisionResolution(m_player, m_walls[i].GetBoundingBox());		
		
		for (int j = 0; j < m_spiders.size(); j++)
		{
			if (CollisionResolution(&m_spiders[j], m_walls[i].GetBoundingBox()))
			{
				m_spiders[j].OnCollision();
			}			
		}

		for (int j = 0; j < m_bats.size(); j++)
		{
			if (CollisionResolution(&m_bats[j], m_walls[i].GetBoundingBox()))
			{
				m_bats[j].OnCollision();
			}
		}
	}

	//Collision Check with Doors
	for (int i = 0; i < m_doors.size(); i++)
	{
		if (!m_doors[i].isOpened())
		{
			if (CollisionResolution(m_player, m_doors[i].GetBoundingBox()))
			{
				m_player->PlayerDoorCollisionResolution(m_doors[i]);
			}
		}
		
		for (int j = 0; j < m_spiders.size(); j++)
		{			
			CollisionResolution(&m_spiders[j], m_doors[i].GetBoundingBox());
		}

		for (int j = 0; j < m_bats.size(); j++)
		{
			CollisionResolution(&m_bats[j], m_doors[i].GetBoundingBox());
		}
	}

	//#######################################################################################

	//Collision Check with Potions
	for (int i = 0; i < m_potions.size(); i++)
	{
		m_player->PlayerPotionCollisionResolution(m_potions[i]);
	}

	//Collision Check with Keys
	for (int i = 0; i < m_keys.size(); i++)
	{
		m_player->PlayerKeyCollisionResolution(m_keys[i]);
	}

	//Collision Check with player
	for (int i = 0; i < m_spiders.size(); i++)
	{
		m_spiders[i].EnemyCollisionResolution(m_player);
	}

	for (int i = 0; i < m_bats.size(); i++)
	{
		m_bats[i].EnemyCollisionResolution(m_player);
	}

	for (int i = 0; i < m_traps.size(); i++)
	{
		m_traps[i].TrapCollisionResolution(m_player);
	}

	//Collision Check Stair with Player to Load Next Level
	for (int i = 0; i < m_stair.size(); i++)
	{
		if (m_player->GetBoundingBox().intersects(m_stair[i].GetBoundingBox()))
		{
			m_load_next_level = true;
			std::cout << "Loading Next Level" << std::endl;
		}
	}

	//GAME OVER
	if (m_player->GetHealth() <= 0)
	{
		m_game_over = true;
		std::cout << "Game over! Loading First Level" << std::endl;
	}
}

bool Game::loadFromFile(std::string file)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());
	tinyxml2::XMLElement *mapEl = doc.FirstChildElement("map");
	if (mapEl == NULL) {
		std::cout << "Error, cannot find Map Element in " << file << std::endl;
		return false;
	}
	
	tinyxml2::XMLElement *tilesetEl = mapEl->FirstChildElement("tileset");

	m_tileset = new TileSet();
	m_tileset->loadFromXML(tilesetEl);

	m_width = mapEl->IntAttribute("width");
	m_height = mapEl->IntAttribute("height");
	m_tileWidth = mapEl->IntAttribute("tilewidth");
	m_tileHeight = mapEl->IntAttribute("tileheight");

	tinyxml2::XMLElement *layerEl = mapEl->FirstChildElement("layer");
	while (layerEl != NULL) {
		//Node Name
		const char *value = layerEl->Attribute("name");
		
		//Load Tiles From Layer
		loadLayerFromXML(layerEl, value);	

		//Next Node
		layerEl = layerEl->NextSiblingElement("layer");
	}
	return true;
}

void Game::loadLayerFromXML(tinyxml2::XMLElement *el, const char *value)
{
	float width = el->IntAttribute("width");
	float height = el->IntAttribute("height");
	tinyxml2::XMLElement *dataEl = el->FirstChildElement("data");
	tinyxml2::XMLElement *tileEl = dataEl->FirstChildElement("tile");

	int x = 0;
	int y = 0;
	while (tileEl != NULL)
	{
		unsigned int id = tileEl->IntAttribute("gid");

		if (id > 0)
		{			
			//Create Tile
			if (strcmp(value, "Wall") == 0)
			{
				m_walls.push_back(
					Wall(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
						, m_tileset->GetTileSize()
						, id
						, m_tileset));
			}
			else if (strcmp(value, "Door") == 0)
			{
				m_doors.push_back(Door(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
								, m_tileset->GetTileSize()
								, id
								, m_tileset));
			}
			else if (strcmp(value, "Trap") == 0)
			{
				m_traps.push_back(Trap(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
					, m_tileset->GetTileSize()
					, id
					, m_tileset
					, TRAP_DAMAGE * m_difficulty_modifier));
			}
			else if (strcmp(value, "Potion") == 0)
			{
				m_potions.push_back(Potion(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
					, m_tileset->GetTileSize()
					, id
					, m_tileset
					, 30.0f));
			}
			else if (strcmp(value, "Key") == 0)
			{
				m_keys.push_back(Key(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
					, m_tileset->GetTileSize()
					, id
					, m_tileset));
			}
			else if (strcmp(value, "Background") == 0)
			{
				m_background.push_back(Background(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
									, m_tileset->GetTileSize()
									, id
									, m_tileset));
			}
			else if (strcmp(value, "SpiderSpawnPoints") == 0)
			{
				m_spider_spawn_point.push_back(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y));
			}
			else if (strcmp(value, "BatSpawnPoints") == 0)
			{
				m_bat_spawn_point.push_back(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y));
			}
			else if (strcmp(value, "PlayerSpawnPoint") == 0)
			{
				m_player_spawn = sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y);
			}			
			else if (strcmp(value, "Stair") == 0)
			{
				m_stair.push_back(
					Stair(sf::Vector2f(m_tileset->getTileSize().x * x, m_tileset->getTileSize().y * y)
					, m_tileset->GetTileSize()
					, id
					, m_tileset));
			}
		}
		

		x++;
		if (x >= width)
		{
			x = 0;
			y++;
		}
		tileEl = tileEl->NextSiblingElement("tile");
	}
	//y then x.
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{	
	for (int i = 0; i < m_background.size(); i++)
	{
		target.draw(m_background[i], states);
	}

	for (int i = 0; i < m_walls.size(); i++)
	{
		target.draw(m_walls[i], states);
	}

	for (int i = 0; i < m_doors.size(); i++)
	{
		target.draw(m_doors[i], states);
	}

	for (int i = 0; i < m_traps.size(); i++)
	{
		target.draw(m_traps[i], states);
	}

	for (int i = 0; i < m_potions.size(); i++)
	{
		target.draw(m_potions[i], states);
	}

	for (int i = 0; i < m_keys.size(); i++)
	{
		target.draw(m_keys[i], states);
	}

	for (int i = 0; i < m_stair.size(); i++)
	{
		target.draw(m_stair[i], states);
	}

	for (int i = 0; i < m_spiders.size(); i++)
	{
		target.draw(m_spiders[i], states);
	}

	for (int i = 0; i < m_bats.size(); i++)
	{
		target.draw(m_bats[i], states);
	}

	target.draw(*m_player, states);

	// Create a text for health
	//FIX ME ## FIGURE OUT HOW TO HANDLE THIS
	sf::Text health_text(std::to_string(m_player->GetHealth()), m_font);
	health_text.setCharacterSize(20);
	health_text.setStyle(sf::Text::Bold);
	health_text.setColor(sf::Color::Yellow);
	health_text.setPosition(sf::Vector2f(20.0f, 0.0f));

	// Create a text for key
	sf::Text key_text(std::to_string(m_player->GetKey()), m_font);
	key_text.setCharacterSize(20);
	key_text.setStyle(sf::Text::Bold);
	key_text.setColor(sf::Color::Yellow);
	key_text.setPosition(sf::Vector2f(20.0f, 30.0f));
	
	target.draw(health_text, states);
	
	target.draw(key_text, states);
}

bool Game::CollisionResolution(GameEntity *g, sf::FloatRect boundig_box)
{
	sf::FloatRect area;
	if (g->GetBoundingBox().intersects(boundig_box, area))
	{
		// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
		if (area.width > area.height)
		{
			if (area.contains({ area.left, g->GetPosition().y }))
			{
				// Up side crash
				g->SetPosition({ g->GetPosition().x, g->GetPosition().y + area.height });
			}
			else
			{
				// Down side crash
				g->SetPosition({ g->GetPosition().x, g->GetPosition().y - area.height });
			}
		}
		else if (area.width < area.height)
		{
			if (area.contains({ g->GetPosition().x + g->GetBoundingBox().width - 1.f, area.top + 1.f }))
			{
				//Right side crash
				g->SetPosition({ g->GetPosition().x - area.width, g->GetPosition().y });
			}
			else
			{
				//Left side crash
				g->SetPosition({ g->GetPosition().x + area.width, g->GetPosition().y });
			}
		}

		return true;
	}
	return false;
}