#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "textureManager.hpp"
#include "direction.hpp"
#include "Anim_Base.hpp"
#include "Anim_Directional.hpp"

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet {
private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_direction;
	std::string m_animType;
	Animations m_animations;
	Anim_Base* m_animationCurrent;
	TextureManager* m_textureManager;
public:
	SpriteSheet(TextureManager* l_textMgr);
	~SpriteSheet();
	void CropSprite(const sf::IntRect &l_rect);
	bool LoadSheet(const std::string &file);
	void ReleaseSheet();

	sf::Vector2i GetSpriteSize();
	sf::Vector2f GetSpritePosition();
	Direction GetDirection();

	Anim_Base* GetCurrentAnim();
	bool SetAnimation(const std::string &l_name,
		const bool &l_play = false,
		const bool &l_loop = false);

	void Update(const float &l_dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);

	void SetSpriteSize(const sf::Vector2i &l_size);
	void SetSpritePosition(const sf::Vector2f &l_pos);
	void SetSpriteDirection(const Direction &l_dir);
	
};

#endif // SPRITE_SHEET_HPP