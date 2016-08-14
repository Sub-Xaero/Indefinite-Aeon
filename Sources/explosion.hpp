#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "includes.hpp"
#include "textureManager.hpp"
#include "defines.hpp"

struct Explosion : public sf::Drawable {
	Explosion(sf::Vector2f pos);

	sf::Sprite Sprite;

	void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	};


#endif // EXPLOSION_HPP

