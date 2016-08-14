#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "includes.hpp"

class TextureManager {
	private:
		map<std::string, sf::Texture> textures;

	public:
		bool loadTexture (const string &name, const string &filename);
		sf::Texture &operator[] (const string &texture);
	};

extern	TextureManager textureManager;

#endif // TEXTURE_MANAGER

