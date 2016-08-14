#ifndef ALIEN_INVADER_HPP
#define ALIEN_INVADER_HPP

#include "includes.hpp"
#include "textureManager.hpp"
#include "defines.hpp"

struct Alien : public sf::Drawable {
	Alien();

	int health, maxHealth, shotRate;

	sf::Clock shootClock;

	sf::Sprite Sprite;

	void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	};


#endif // ALIEN_INVADER_HPP

