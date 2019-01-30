#pragma once

#include <string>
#include <vector>
#include "SpriteSheet.hpp"
#include "TextureManager.hpp"
#include "Tile.hpp"

class Tile;

class UniqueTile {
private:
	std::vector<sf::Sprite*> spriteTable;
	SpriteSheet sheet;
	TextureManager* tex;
	unsigned int UID;
	std::string type;
public:
	UniqueTile(unsigned int UID, TextureManager* tex) :
		UID(UID), tex(tex), sheet(tex)
	{}
	void appendSprite(sf::Sprite* l_sprite);
	void setupSpriteTable(std::string file);
	void setAnimation(std::string name, bool play = true, bool loop = true);
	void updateFrame(float dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);
	std::string getType();
	void setType(std::string tileType);
	~UniqueTile() {
		sheet.ReleaseSheet();
	}
};