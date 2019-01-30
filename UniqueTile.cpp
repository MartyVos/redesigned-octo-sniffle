#include "UniqueTile.hpp"
#include "Tile.hpp"

void UniqueTile::appendSprite(sf::Sprite* l_sprite) {
	spriteTable.push_back(l_sprite);
}

void UniqueTile::setupSpriteTable(std::string file) {
	this->sheet.SetSpriteTable(spriteTable);
	this->sheet.LoadSheet(file);
}

void UniqueTile::setAnimation(std::string name, bool play, bool loop) {
	this->sheet.SetAnimation(name, play, loop);
}

void UniqueTile::updateFrame(float dT) {
	this->sheet.Update(dT);
}

void UniqueTile::draw(std::shared_ptr<sf::RenderWindow> w) {
	this->sheet.draw(w);
}

void UniqueTile::setType(std::string tileType) {
	type = tileType;
}

std::string UniqueTile::getType() {
	return type;
}