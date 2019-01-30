#include "Grid.hpp"
#include <iostream>
//#include "GameObjectsDefault.hpp"

Grid::Grid(std::vector<UniqueTile*> &unique, std::vector<Tile*> &tileVec, std::vector<Tile*> &npcVec, unsigned int width, unsigned int tileSize):
	unique(unique), tileVec(tileVec), npcVec(npcVec), width(width), tileSize(tileSize)
{
	playerTileIndex = tileVec.size() - 1;
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
	for (auto &i : unique) {
		i->updateFrame(dT);
	}/*
	for (auto &i : npcVec) {
		//i->updateFrame(dT);
		//i->move(i->getPath());
	}*/
}

Grid::~Grid() {
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> w) {
	for (auto &i : this->unique) {
		i->draw(w);
	}/*
	for (auto &i : npcVec) {
		//i->draw(w);
	}*/
}

void Grid::setPlayerPosition(sf::Vector2f pos) {
	playerPosition = pos;
	tileVec[playerTileIndex]->setPosition(playerPosition);
}

void Grid::movePlayer(std::string direction) {
	auto step = this->move(playerIndex, 4, direction);
	tileVec[playerTileIndex]->setPosition(playerPosition);
}

int Grid::checkDirection(std::string direction) {
	auto tmp = directionMap.find(direction);
	if (tmp != directionMap.end()) {
		return tmp->second;
	}
	return -2;		//Left is always -1
}

unsigned int Grid::move(unsigned int currentIndex, int ID, std::string direction) {
	auto tmp = checkDirection(direction);
	if (tmp != -2) {
		int futureIndex = static_cast<int>(currentIndex) + tmp;
		if (futureIndex < 0 || futureIndex >= static_cast<int>(tileVec.size())) { return currentIndex; }
		if ((futureIndex == currentIndex-1 && currentIndex % width == 0) ||
			(futureIndex == currentIndex + 1 && currentIndex % width == width - 1)) {
			return currentIndex;
		}
		if (tileVec[futureIndex]->getType() != "solid") {
			currentIndex = futureIndex;
			playerIndex += tmp;
		}
	}
	return static_cast<unsigned int>(currentIndex);
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

unsigned int Grid::getPlayerIndex() {
	return playerIndex;
}

void Grid::setPlayerIndex(unsigned int index) {
	playerIndex = index;
}