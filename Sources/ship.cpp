#include "ship.hpp"

Ship::Ship () {
	Sprite.setTexture (textureManager["Blue Ship"]);
	Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

	Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
	Sprite.setPosition(APP_WIDTH / 2 - Sprite.getGlobalBounds().width / 2, APP_HEIGHT - Sprite.getGlobalBounds().height);
	}

void Ship::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(Sprite, states);
	}
