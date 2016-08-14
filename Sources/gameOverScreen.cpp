#include "includes.hpp"
#include "dynamicMenu.hpp"
#include "resources.hpp"
#include "menus.hpp"
#include "game.hpp"
#include "utilFunctions.hpp"
#include "textureManager.hpp"
#include "settings.hpp"

int gameOverScreen() {
	Menu menu;

	bool toggle = true;

	sf::Clock timer;

	sf::Text Text ("Game Over", Font, MENU_FONT_SIZE * 4);
	Text.setColor(sf::Color::Red);
	Text.setPosition((APP_WIDTH / 2) - Text.getGlobalBounds().width / 2, (APP_HEIGHT / 2) - Text.getGlobalBounds().height / 2 - 120);

	sf::Text Text2 ("Press any Key...", Font, MENU_FONT_SIZE);
	Text2.setPosition((APP_WIDTH / 2) - Text2.getGlobalBounds().width / 2, APP_HEIGHT - Text2.getGlobalBounds().height - 80);

	sf::Texture tex;
	tex.create(App.getSize().x, App.getSize().y);
	tex.update(App);

	sf::Sprite background(tex);

	if (View.getSize().x != App.getSize().x && View.getSize().y != App.getSize().y) {
		float xScale = (double)((double)(View.getSize().x - App.getSize().x) / App.getSize().x);
		float yScale = (double)((double)(View.getSize().y - App.getSize().y) / App.getSize().y);

		background.setScale(xScale > 0 ? 1 + xScale : abs(xScale), yScale > 0 ? 1 + yScale : abs(yScale));
		}
	sf::RectangleShape backgroundOverlay(sf::Vector2f(APP_WIDTH, APP_HEIGHT));
	backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 200));

	auto stopWaiting = [] () {
		if (gameEngine.score > highscores.back().second)
			newHighscoreScreen();
		throw 0;
		};

	menu.suppressTitle = true;
	menu.bindEvents(
		{
			{
			Event.KeyPressed,
			stopWaiting
			},
			{
			Event.MouseButtonPressed,
			stopWaiting
			},

		}
	);

	while (App.isOpen() ) {
		while (App.pollEvent (Event) ) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && menu.eventManager.count ( (sf::Event::EventType) i) == 1) {
					try {
						menu.eventManager[Event.type]();
						}
					catch (int p) {
						if (p == 0)
							return p;
						}
					}
				}
			}

		if (toggle && timer.getElapsedTime().asMilliseconds() > 1) {
			timer.restart();
			Text2.setColor (sf::Color (255, 255, 255, Text2.getColor().a - 4) );
			if (toggle && Text2.getColor().a < 20)
				toggle = false;
			}

		if (!toggle && timer.getElapsedTime().asMilliseconds() > 1) {
			timer.restart();
			Text2.setColor (sf::Color (255, 255, 255, Text2.getColor().a + 4) );
			if (!toggle && Text2.getColor().a > 240)
				toggle = true;
			}

		menu.handle();
		App.clear();
		App.draw(background);
		App.draw(backgroundOverlay);
		App.draw (Text);
		App.draw (Text2);
		App.draw(menu);
		App.display();
		}
	return -1;
	}
