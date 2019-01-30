#pragma once
#include "Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Tile.hpp"
#include "UniqueTile.hpp"

//TODO:	Player als laatste renderen.

class Grid: public Canvas {
private:
	std::vector<Tile*> &tileVec;
	std::vector<UniqueTile*> &unique;
	std::vector<Tile*> &npcVec;
	sf::Vector2f playerPosition;
	unsigned int playerIndex;
	unsigned int playerTileIndex;
	std::map<std::string, int> directionMap;
	unsigned int width;
	unsigned int tileSize;
	
public:
	Grid(std::vector<UniqueTile*> &unique, std::vector<Tile*> &tileVec, std::vector<Tile*> &npcVec, unsigned int width, unsigned int tileSize);
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void onRender()override {}
	void update(float &dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);
	void setPlayerPosition(sf::Vector2f pos);
	void movePlayer(std::string direction);
	int checkDirection(std::string direction);
	void setupMap(nlohmann::json::array_t &gridData);
	unsigned int move(unsigned int currentIndex, int ID, std::string direction);
	sf::Vector2f getPlayerPos();
	unsigned int getPlayerIndex();
	void setPlayerIndex(unsigned int index);
	void moveNPC(unsigned int UID, std::string direction);
	~Grid();
};

