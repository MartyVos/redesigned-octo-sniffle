#pragma once
#include "Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Tile.hpp"

//TODO:	Player als laatste renderen.

class Grid: public Canvas {
private:
	std::vector<Tile*> &tileVec;
	sf::Vector2f playerPosition;
	unsigned int playerIndex;
	unsigned int playerTileIndex;
	std::map<std::string, int> directionMap;
public:
	Grid(std::vector<Tile*> &tileVec);
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void Render(std::shared_ptr<sf::RenderWindow> w) {}
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
	~Grid();
};

