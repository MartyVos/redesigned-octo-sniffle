#pragma once
#include <string>
#include <vector>
#include "SpriteSheet.hpp"
#include "TextureManager.hpp"
#include "UniqueTile.hpp"

//No imagePath, TextureManager uses TileID

class UniqueTile;

class Tile {
private:
	UniqueTile* m_uniqueTile;
	int & id;
	unsigned int UID;		//Tmp: unique prite ID
	unsigned int gridPosition;
	unsigned int currentTime;
	std::string currentDirection;
	std::vector<std::string> path;
	std::vector<unsigned int> time;
	unsigned int patIndex;
public:
	sf::Sprite m_sprite;
	Tile(int id, UniqueTile* l_uniqueTile, unsigned int uid = 0) :
		id(id), m_uniqueTile(l_uniqueTile), UID(uid)
	{}
	~Tile() {}
	void setPosition(sf::Vector2f pos);
	void setScale(sf::Vector2f scale);
	std::string getType();
	unsigned int getUID();
	void setPath(nlohmann::json::array_t paths, nlohmann::json::array_t pathTime);
	std::string getCurrentDirection();
	unsigned int getCurrentTime();
	
};