#pragma once
#include "Grid.hpp"
#include <memory>
#include "Graphics.hpp"
#include <SFML/Graphics.hpp>


// TODO check all includes for duplicates and iostreams

// SFML window requires the renderwindow functions
class GraphicsSFML : public Graphics
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Grid> grid;
public:
	GraphicsSFML() {};
	GraphicsSFML(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid) :window(window), grid(grid) {};

	void render() {
		grid->draw(window);
	};
	~GraphicsSFML() {};
};

