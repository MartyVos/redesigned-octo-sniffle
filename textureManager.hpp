#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "resourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class TextureManager: public ResourceManager<TextureManager, sf::Texture> {
public:
	TextureManager(std::vector<std::string> sheetPaths):
		ResourceManager(sheetPaths)
	{}

	sf::Texture* Load(const std::string& l_path);
};

#endif // TEXTURE_MANAGER_HPP