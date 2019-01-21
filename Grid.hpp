#pragma once
#include "Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

//TODO:	Player als laatste renderen.

class Grid: public Canvas {
private:
	std::vector<Tile*> &tileVec;
	sf::Vector2f playerPosition;
	unsigned int playerIndex;
public:
	Grid(std::vector<Tile*> &tileVec);
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void onRender()override {}
	void update(float &dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);
	void setPlayerPosition(sf::Vector2f pos);
	void movePlayer(sf::Vector2f delta);
	~Grid();
};

