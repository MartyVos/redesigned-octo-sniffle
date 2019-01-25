/*
TODO:	Make flyweight:
			Why:
				Duplicate tiles are generated which causes longer loading times
				For example: The loading time of a grid (10x8 tiles) is around
				3 seconds.
*/

#include <iostream>
#include "TextureManager.hpp"
#include "Tile.hpp"
#include "json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <array>

//Deze wordt gebruikt om een JSON-object 'mooi' naar een file wordt geschreven.
#include <iomanip>

#include "GraphicsSFML.hpp"
#include "Grid.hpp"

//Globaal, weet ik. Is maar tijdelijk.
static unsigned int width;
static unsigned int tileSize = 64;


//Deze functie leest de spelers index uit een save file
unsigned int readIndex(std::string saveFile) {
	std::ifstream file(saveFile);
	nlohmann::json J;
	file >> J;
	return J["data"]["player"]["position"];
}

//Deze funtie slaat de spelers index op in een save file
//De JSON structuur is echter alfabetisch geordend.
void saveIndex(unsigned int index, std::string saveFile) {
	std::ifstream in(saveFile);
	nlohmann::json J;
	in >> J;
	in.close();

	std::ofstream out(saveFile, std::ios::ate);
	J["data"]["player"]["position"] = index;
	out << std::setw(4) << J;
	out.close();
}

//Deze functie converteert een std::vector index naar sf::Vector2f
sf::Vector2f convertIndextoCoords(unsigned int index) {
	//TODO:	make map width + scaling private vars
	int m_index = static_cast<int>(index);
	int c = 0;
	while (m_index >= 0) {
		if ((m_index -= width) < 0) {
			m_index += width;
			break;
		}
		else {
			c++;			
		}
	}
	auto coords = sf::Vector2f{ static_cast<float>(m_index)*tileSize, static_cast<float>(c)*tileSize - tileSize };
	return coords;
}

//Deze functie converteert sf::Vector2f naar een std::vector index.
unsigned int convertCoordsToIndex(sf::Vector2f coordinate) {
	//TODO:	make map width + scaling private vars
	auto index = static_cast<unsigned int>(coordinate.x) + static_cast<unsigned int>((coordinate.y * width));
	return index / tileSize;
}

//Deze functie delete een object uit een std::vector<T*>
template<typename T>
void destroy_vector(std::vector<T*> &v) {
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}

//Deze functie haalt tiles uit een JSON-object en returnt een std::vector<Tile*>
std::vector<Tile*> getTiles(nlohmann::json &J, TextureManager &tex) {
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
		
		std::string blockType = gfxID["type"];
		int tileSize = gfxID["size"][0];
		int tileScale = gfxID["scale"][0];
		std::string animName = gfxID["anim_name"];

		float x = static_cast<float>(index*tileSize*tileScale);
		float y = static_cast<float>(r*tileSize*tileScale);

		tileVec.push_back(new Tile{ type,&tex,animName });
		tileVec[i]->setPosition(sf::Vector2f{ x, y });
		tileVec[i]->setType(blockType);
		if (index == width - 1) {
			r++;
		}
	}
	return tileVec;
}

int main() {
    std::vector<std::string> paths = { "grid.json" };
	TextureManager tex(paths);

	nlohmann::json J;
	std::ifstream IN("grid.json");
	IN >> J;
	IN.close();

	width = J["data"]["grid"]["width"];

	auto tiles = getTiles(J, tex);

	//Voorlopig is de speler een Tile met ID 4
	int playerID = 4;
	Tile* player = new Tile{ playerID,&tex,"Player" };
	tiles.push_back(player);

	auto sharedG = std::make_shared<Grid>(tiles);

	//Set de steps die de speler moet nemen om omhoog,omlaag,links en rechts te kunnen bewegen.
	nlohmann::json::array_t directions = J["data"]["grid"]["next_position"];	
	sharedG->setupMap(directions);

	unsigned int initIndex = readIndex("save.json");
	sharedG->setPlayerPosition(convertIndextoCoords(initIndex));	//Set de spelers positie
	sharedG->setPlayerIndex(initIndex);								//Set de spelers grid index 

	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640,480 }, "PocketAnimals Grid Test");

	GraphicsSFML gs(window, sharedG);
	//Tijdsverschil (dT) tussen frames
	float dT = 25.f;

	//Set de view (of camera) ter grootte van het scherm en focused op de speler.
	sf::View view1;
	view1.setSize(sf::Vector2f{ 640.f,480.f });	
	//Deze setCenter is nodig voor de initialisatie
	view1.setCenter(sharedG->getPlayerPos());

	while (window->isOpen()) {
		window->setVerticalSyncEnabled(true);
		window->setView(view1);
		window->clear();

		gs.render();
		sharedG->update(dT);
		window->display();
		sf::sleep(sf::milliseconds(20));
		sf::Event event;
		unsigned int step = 0;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				saveIndex(sharedG->getPlayerIndex(), "save.json");
				window->close();
				destroy_vector<Tile>(tiles);
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					step = sharedG->move(sharedG->getPlayerIndex(), playerID, "up");
					sharedG->setPlayerPosition(convertIndextoCoords(step));
					break;
				case sf::Keyboard::A:
					step = sharedG->move(sharedG->getPlayerIndex(), playerID, "left");
					sharedG->setPlayerPosition(convertIndextoCoords(step));
					break;
				case sf::Keyboard::S:
					step = sharedG->move(sharedG->getPlayerIndex(), playerID, "down");
					sharedG->setPlayerPosition(convertIndextoCoords(step));
					break;
				case sf::Keyboard::D:
					step = sharedG->move(sharedG->getPlayerIndex(), playerID, "right");
					sharedG->setPlayerPosition(convertIndextoCoords(step));
					break;
				default:
					break;
				}
				view1.setCenter(sharedG->getPlayerPos());
			}
		}
	}
	return 0;
}

