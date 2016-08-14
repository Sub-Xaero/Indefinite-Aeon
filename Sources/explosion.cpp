#include "explosion.hpp"

Explosion::Explosion (sf::Vector2f pos) {
	Sprite.setTexture (textureManager["Explosion"]);
	Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

	Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
	Sprite.setPosition(pos);
	}

void Explosion::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(Sprite, states);
	}
