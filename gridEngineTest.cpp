#include <iostream>
#include "textureManager.hpp"
#include "Tile.hpp"
#include "json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "GraphicsSFML.hpp"
#include "Grid.hpp"


template<typename T>
void destroy_vector(std::vector<T*> &v) {
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}

//TODO:	Make Player Texture

std::vector<Tile*> getTiles(std::string filename, TextureManager &tex) {
	std::ifstream file(filename);
	nlohmann::json J;
	file >> J;

	nlohmann::json::array_t tileArray = J["data"]["grid"]["tiles"];
	nlohmann::json::array_t gfxData = J["data"]["grid"]["gfx"];
	unsigned int arraySize = tileArray.size();
	std::vector<Tile*> tileVec;
	
	unsigned int r = 0;
	unsigned int width = J["data"]["grid"]["width"];

	for (unsigned int i = 0; i < arraySize; i++) {
		unsigned int index = i % width;

		nlohmann::json::object_t tileID = tileArray[i][std::to_string(i)];
		
		int type = tileID["type"];
		nlohmann::json::object_t gfxID = gfxData[type][std::to_string(type)];
		int tileSize = gfxID["size"][0];
		int tileScale = gfxID["scale"][0];

		std::string animName = gfxID["anim_name"];

		float x = static_cast<float>(index*tileSize*tileScale);
		float y = static_cast<float>(r*tileSize*tileScale);
		tileVec.push_back(new Tile{ type,&tex,animName });
		tileVec[i]->setPosition(sf::Vector2f{ x, y });

		if (index == width - 1) {
			r++;
		}
	}
	return tileVec;
}

int main() {
    std::vector<std::string> paths = { "grid.json" };
	TextureManager tex(paths);

	auto tiles = getTiles("grid.json", tex);
	
	int playerID = 4;
	Tile* player = new Tile{ playerID,&tex,"32Test" };
	tiles.push_back(player);

	auto sharedG = std::make_shared<Grid>(tiles);
	sharedG->setPlayerPosition(sf::Vector2f{ 64.f,64.f });

	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640,480 }, "PocketAnimals Grid Test");

	GraphicsSFML gs(window, sharedG);
	float dT = 25.f;

	while (window->isOpen()) {
		window->clear();

		gs.render();
		sharedG->update(dT);
		window->display();

		sf::sleep(sf::milliseconds(20));
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				destroy_vector<Tile>(tiles);
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
					//TODO:	delta moet gescaled worden.
				case sf::Keyboard::W:
					sharedG->setPlayerPosition(sf::Vector2f{ 0.f,-10.f });
					break;
				case sf::Keyboard::A:
					sharedG->setPlayerPosition(sf::Vector2f{ -10.f,0.f });
					break;
				case sf::Keyboard::S:
					sharedG->setPlayerPosition(sf::Vector2f{ 0.f,+10.f });
					break;
				case sf::Keyboard::D:
					sharedG->setPlayerPosition(sf::Vector2f{ +10.f,0.f });
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}

