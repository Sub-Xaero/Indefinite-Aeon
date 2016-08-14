#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include "includes.hpp"
#include "textureManager.hpp"
#include "defines.hpp"

struct Ship : public sf::Drawable {
	Ship();

	sf::Clock moveClock;
	sf::Clock shootClock;

	bool moving = false;

	const int maxHealth = 100;
	int health = maxHealth, damage = 25, level = 1;

	sf::Sprite Sprite;

	void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	};


#endif // PLAYER_SHIP_HPP

