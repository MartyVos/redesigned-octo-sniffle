#include "TextureManager.hpp"

sf::Texture* TextureManager::Load(const std::string& l_path) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(
		l_path))
	{
		delete texture;
		texture = nullptr;
		std::cerr << "! Failed to load texture: "
			<< l_path << std::endl;
	}
	return texture;
}