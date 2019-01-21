#include "Tile.hpp"

void Tile::draw(std::shared_ptr<sf::RenderWindow> w) {
	sheet.draw(w);
}

void Tile::setPosition(sf::Vector2f pos) {
	sheet.SetSpritePosition(pos);
}

void Tile::updateFrame(float &dT) {
	sheet.Update(dT);
}

void Tile::setAnimation(bool play, bool loop) {
	sheet.SetAnimation(name, play, loop);
}