#include "Grid.hpp"
#include <iostream>
//#include "GameObjectsDefault.hpp"

Grid::Grid(std::vector<Tile*> &tileVec):
	tileVec(tileVec)
{
	playerIndex = tileVec.size() - 1;
}

// TODO validMove
// checking if the value suggested position is allowed inside the grid
bool Grid::validMove(int currentIndex, int direction) {

	// should contain the following:

	// try catch statement to declare value in the array
	// return true if succesfull
	// return false if error occurs
	return false;
}
// current index
// id to seperate from currentindex values
// direction is up down left right
int Grid::move(int currentIndex, int ID, int direction) {
	return 0;
}

int Grid::getType(int currentIndex, int direction) {
	return 0;
}

void Grid::update(float &dT) {
	for (auto &i : tileVec) {
		i->updateFrame(dT);
	}
}

Grid::~Grid() {
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> w) {
	for (auto &i : tileVec) {
		i->draw(w);
	}
}

void Grid::setPlayerPosition(sf::Vector2f delta) {
	playerPosition += delta;
	tileVec[playerIndex]->setPosition(playerPosition);
}
