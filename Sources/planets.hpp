#ifndef PLANETS_HPP
#define PLANETS_HPP

#include "includes.hpp"

struct Planet : public sf::Drawable {
	Planet();

	bool leftRotate;

	sf::Sprite Sprite;

	void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	};


#endif // PLANETS_HPP

