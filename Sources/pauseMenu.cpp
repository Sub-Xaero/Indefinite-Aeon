#include "includes.hpp"
#include "dynamicMenu.hpp"
#include "resources.hpp"
#include "menus.hpp"
#include "game.hpp"
#include "utilFunctions.hpp"
#include "textureManager.hpp"
#include "settings.hpp"

int pauseMenu () {
	Menu menu;

	class Buttons {
			enum {
				ResumeGame,
				OptionsMenu,
				CreditsMenu,
				Quit
				};
		};

	menu.setTitle("Pause Menu");

	menu.bindEvent (sf::Event::KeyPressed, [&] {if (Event.key.code == sf::Keyboard::Key::Escape) throw 0;});
	menu.newButton ("Resume Game").setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White) = [] {throw 0;};
	menu.newButton ("Options").mimicStyles (menu[0]) = [] {optionsMenu();};
	menu.newButton ("Credits").mimicStyles (menu[0]) = [] {creditsMenu();};
	menu.newButton ("Quit").mimicStyles (menu[0]) = [] {gameEngine.gameQuit = true; throw (0);};

	sf::Texture tex;
	tex.create(App.getSize().x, App.getSize().y);
	tex.update(App);

	sf::Sprite background(tex);
	sf::Sprite underlay(textureManager["Pause Screen"]);

	if (View.getSize().x != App.getSize().x && View.getSize().y != App.getSize().y) {
		float xScale = (double)((double)(View.getSize().x - App.getSize().x) / App.getSize().x);
		float yScale = (double)((double)(View.getSize().y - App.getSize().y) / App.getSize().y);

		background.setScale(xScale > 0 ? 1 + xScale : abs(xScale), yScale > 0 ? 1 + yScale : abs(yScale));
		}
	sf::RectangleShape backgroundOverlay(sf::Vector2f(APP_WIDTH, APP_HEIGHT));
	backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 200));

	while (App.isOpen() ) {
		while (App.pollEvent (Event) ) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && menu.eventManager.count ( (sf::Event::EventType) i) == 1) {
					try {
						menu.eventManager[Event.type]();
						}
					catch (int p) {
						if (p == 0) return p;
						}
					}
				}
			}
		menu.handle();
		App.clear();
		App.draw(background);
		App.draw(backgroundOverlay);
		//App.draw(underlay);
		App.draw(menu);
		App.display();
		}
	return -1;
	}
