#include "Tile.hpp"
#include "UniqueTile.hpp"

void Tile::setPosition(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

void Tile::setScale(sf::Vector2f scale) {
	m_sprite.setScale(scale);
}

std::string Tile::getType() {
	return this->m_uniqueTile->getType();
}

unsigned int Tile::getUID() {
	return UID;
}

void Tile::setPath(nlohmann::json::array_t paths, nlohmann::json::array_t pathTime) {
	for (unsigned int i = 0; i < paths.size(); i++) {
		this->path.push_back(paths[i]);
		this->time.push_back(pathTime[i]);
	}
	this->currentDirection = path[0];
	this->currentTime = time[0];
}

std::string Tile::getCurrentDirection() {
	return currentDirection;
}

unsigned int Tile::getCurrentTime() {
	return currentTime;
}