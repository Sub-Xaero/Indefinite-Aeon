#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"
#include "save.hpp"

int splashScreen() {
	Menu menu;

	sf::Texture splashTexture;
	splashTexture.loadFromFile ("Graphics/Logo.png");

	bool stage2 = false;

	sf::Sprite splash (splashTexture);
	splash.setColor (sf::Color (255, 255, 255, 0) );

	sf::Clock timer;

	while (App.isOpen() ) {
		while (App.pollEvent (Event) ) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && menu.eventManager.count ( (sf::Event::EventType) i) == 1) {
					try {
						menu.eventManager[Event.type]();
						}
					catch (int p) {
						return 0;
						}
					}
				}
			}
		if (!stage2 && timer.getElapsedTime().asMilliseconds() > 1)
			timer.restart(), splash.setColor (sf::Color (255, 255, 255, splash.getColor().a + 2.5) );

		if (!stage2 && splash.getColor().a > 240)
			stage2 = true;

		if (stage2 && timer.getElapsedTime().asMilliseconds() > 1)
			timer.restart(), splash.setColor (sf::Color (255, 255, 255, splash.getColor().a - 2.5) );

		if (stage2 && splash.getColor().a < 20)
			return 0;

		menu.handle();
		App.clear();
		App.draw (splash);
		App.display();
		Framerate.restart();
		}
	return 0;
	}

