#pragma once
#include <string>
#include "SpriteSheet.hpp"
#include "TextureManager.hpp"

//No imagePath, TextureManager uses TileID

class Tile {
private:
	int & id;
	SpriteSheet sheet;
	TextureManager* tex;
	unsigned int gridPosition;
	std::string name;
	std::string type;
public:
	Tile(int & id, TextureManager* tex, std::string animationName):
		id(id), tex(tex), sheet(tex), name(animationName)
	{
		this->sheet.LoadSheet(std::to_string(id));
		this->setAnimation();
	};
	~Tile() { this->sheet.ReleaseSheet(); }
	void draw(std::shared_ptr<sf::RenderWindow> w);
	void setPosition(sf::Vector2f pos);
	void updateFrame(float &dT);
	void setAnimation(bool play = true, bool loop = true);
	void setType(std::string l_type);
	std::string getType();
};

