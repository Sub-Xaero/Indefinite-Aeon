#include "textureManager.hpp"

bool TextureManager::loadTexture (const std::string &name, const std::string &filename) {
	sf::Texture tex;
	if (!tex.loadFromFile (filename) )
		return false;

	this->textures[name] = tex;
	return true;
	}

sf::Texture &TextureManager::operator[] (const std::string &texture) {
	return this->textures[texture];
	}

TextureManager textureManager;
