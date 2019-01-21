#pragma once
#include "Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"

class Grid: public Canvas {
private:
	std::vector<Tile*> &tileVec;
public:
	Grid(std::vector<Tile*> &tileVec);
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void onRender()override {}
	void update(float &dT) {
		for (auto &i : tileVec) {
			i->updateFrame(dT);
		} 
	}
	void draw(std::shared_ptr<sf::RenderWindow> w);
	~Grid();
};

