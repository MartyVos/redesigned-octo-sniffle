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

void Grid::setPlayerPosition(sf::Vector2f pos) {
	playerPosition = pos;
	tileVec[playerIndex]->setPosition(playerPosition);
}

void Grid::movePlayer(sf::Vector2f delta) {
	playerPosition += delta;
	tileVec[playerIndex]->setPosition(playerPosition);
}

int Grid::checkDirection(std::string direction) {
	auto tmp = directionMap.find(direction);
	if (tmp != directionMap.end()) {
		return tmp->second;
	}
	return -2;		//Left is always -1
}

int Grid::move(int currentIndex, int ID, std::string direction) {
	auto tmp = checkDirection(direction);
	if (tmp != -2) {
		currentIndex += tmp;
	}
	return currentIndex;
}

void Grid::setupMap(nlohmann::json::array_t &gridData) {
	directionMap.emplace("left", gridData[0]["left"]);
	directionMap.emplace("right", gridData[1]["right"]);
	directionMap.emplace("up", gridData[2]["up"]);
	directionMap.emplace("down", gridData[3]["down"]);
}

sf::Vector2f Grid::getPlayerPos() {
	return playerPosition;
}