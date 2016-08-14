#include "planets.hpp"
#include "textureManager.hpp"
#include "defines.hpp"
#include "game.hpp"

Planet::Planet () {
	int type = rand() % 2 + 1;
	leftRotate = (rand() % 2 + 1 == 1);

	Sprite.setTexture (type == 1 ? textureManager["Planet1"] : textureManager["Planet2"]);
	Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
	Sprite.setPosition(rand() % APP_WIDTH, 0);
	}

void Planet::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(Sprite, states);
	}

