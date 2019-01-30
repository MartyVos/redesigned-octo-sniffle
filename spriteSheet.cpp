#include "spriteSheet.hpp"
#include "AnimBase.hpp"
#include "AnimDirectional.hpp"

SpriteSheet::SpriteSheet(TextureManager* l_textMgr) :
	m_textureManager(l_textMgr),
	m_animationCurrent(nullptr),
	m_spriteScale(1.f, 1.f),
	m_direction(Direction::Right)
{}

SpriteSheet::~SpriteSheet() { ReleaseSheet(); }

void SpriteSheet::ReleaseSheet() {
	m_textureManager->ReleaseResource(m_texture);
	m_animationCurrent = nullptr;
	while (m_animations.begin() != m_animations.end()) {
		delete m_animations.begin()->second;
		m_animations.erase(m_animations.begin());
	}
}

void SpriteSheet::SetSpriteSize(const sf::Vector2i &l_size) {
	m_spriteSize = l_size;
}

void SpriteSheet::SetSpriteDirection(const Direction &l_dir) {
	if (l_dir == m_direction) { return; }
	m_direction = l_dir;
	m_animationCurrent->CropSprite();
}

void SpriteSheet::CropSprite(const sf::IntRect &l_rect) {
	for (auto &i : spriteTable) {
		i->setTextureRect(l_rect);
	}
}

bool SpriteSheet::SetAnimation(const std::string &l_name,
	const bool &l_play,
	const bool &l_loop)
{
	auto itr = m_animations.find(l_name);		//Can't set loop?
	if (itr == m_animations.end()) { return false; }

	//Looping problem fixed when removed.
	//if (itr->second == m_animationCurrent) { std::cout << "CURRENT ANIM" << std::endl; return false; }
	if (m_animationCurrent) { m_animationCurrent->Stop(); }
	m_animationCurrent = itr->second;
	m_animationCurrent->SetLooping(l_loop);
	if (l_play) { m_animationCurrent->Play(); }
	m_animationCurrent->CropSprite();
	return true;
}

AnimBase* SpriteSheet::GetCurrentAnim() {
	return m_animationCurrent;
}

void SpriteSheet::Update(const float &l_dT) {
	m_animationCurrent->Update(l_dT);
}

void SpriteSheet::draw(std::shared_ptr<sf::RenderWindow> w) {
	for (auto &i : this->spriteTable) {
		w->draw(*i);
	}
}

sf::Vector2i SpriteSheet::GetSpriteSize() {
	return m_spriteSize;
}

Direction SpriteSheet::GetDirection() {
	return m_direction;
}

bool SpriteSheet::LoadSheet(const std::string &l_file) {
	std::ifstream sheet;
	sheet.open("grid.json");
	json j;

	bool invalidID = false;

	if (sheet.is_open()) {
		ReleaseSheet();
		sheet >> j;
		json::array_t tileData = j["data"]["grid"]["gfx"];
		std::string texture;
		json::array_t tileset = j["data"]["grid"]["tileset"];
		
		std::string tmp = "0";		//Tmp hardcoded tileset
		unsigned int ID;
		unsigned int tileDataSize = tileData.size();

		if (static_cast<unsigned int>(std::stoi(l_file)) >= tileDataSize) {
			//Invalid tile -> missing texture
			invalidID = true;
			texture = tmp;
			ID = 0;			//Default
		}
		else {
			for (unsigned int i = 0; i < tileDataSize; i++) {
				if (l_file == std::to_string(i)) {
					texture = tmp;
					ID = i;
					break;
				}
			}
		}
		
		
		if (m_texture != "") {
			std::cerr << "! Duplicate texture entries in: "
				<< l_file << std::endl;
			
		}
		if (!m_textureManager->RequireResource(texture)) {
			std::cerr << "! Could not set up the texture: "
				<< texture << std::endl;
			
		}

		m_texture = texture;

		for (auto &i : spriteTable) {
			i->setTexture(*m_textureManager->GetResource(m_texture));
		}
		json::object_t tileID = tileData[ID][std::to_string(ID)];
		
		auto scale = tileID["scale"];
		this->m_spriteScale.x = scale[0];
		this->m_spriteScale.y = scale[1];
		for (auto &i : spriteTable) {
			i->setScale(this->m_spriteScale);
		}

		auto sizes = tileID["size"];
		m_spriteSize.x = sizes[0];
		m_spriteSize.y = sizes[1];
		SetSpriteSize(m_spriteSize);
		
		auto animName = tileID["anim_name"];
		json::string_t animType = tileID["anim_type"];
		m_animType = animType;
		std::string name = animName;
		if (m_animations.find(name) != m_animations.end()) {
			std::cerr << "! Duplicate animation(" << name
				<< ") in: " << l_file << std::endl;
		}
		//std::cout << name << std::endl;		//Animation overwritten
		AnimBase* anim = nullptr;
		if (m_animType == "Directional") {
			anim = new AnimDirectional();
		}
		else {
			std::cerr << "! Unknown animation type: "
				<< m_animType << std::endl;
		}

		auto animData = tileID["anim"];

		//If invalid
		if (invalidID) {
			anim->m_frameStart = 2;
			anim->m_frameEnd = 2;
			anim->m_frameRow = 0;
			anim->m_frameTime = animData[3];
			anim->m_frameActionStart = -1;
			anim->m_frameActionEnd = -1;
		}
		else {
			anim->m_frameStart = animData[0];
			anim->m_frameEnd = animData[1];
			anim->m_frameRow = animData[2];
			anim->m_frameTime = animData[3];
			anim->m_frameActionStart = animData[4];
			anim->m_frameActionEnd = animData[5];
		}

		anim->SetSpriteSheet(this);
		anim->SetName(name);
		anim->Reset();
		this->m_animations.emplace(name, anim);
		if (m_animationCurrent) {}
		m_animationCurrent = anim;
		m_animationCurrent->Play();

		sheet.close();
		return true;
	}
	else {
		std::cerr << "! Failed loading spritesheet: "
			<< l_file << std::endl;
	}
	return false;
}

void SpriteSheet::SetSpriteTable(std::vector<sf::Sprite*> &l_spriteTable) {
	for (auto &i : l_spriteTable) {
		spriteTable.push_back(i);
	}
}

//TODO:	Rewrite gridWindow.cpp for using animations