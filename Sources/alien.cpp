#include "alien.hpp"

Alien::Alien () {
	int type = rand() % 3;

	shotRate = 3 + (rand() % 5 + 1);

	switch (type) {
		case 0:
			Sprite.setTexture (textureManager["Fire Eye"]);
			health = maxHealth = 250;
			break;

		case 1:
			Sprite.setTexture (textureManager["Green Blob"]);
			health = maxHealth = 320;
			break;

		case 2:
			Sprite.setTexture (textureManager["Pink Blob"]);
			health = maxHealth = 100;
			break;

		}

	Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2);
	Sprite.setPosition(rand() % (APP_WIDTH - 100) + 100, 0);
	}

void Alien::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(Sprite, states);
	}
