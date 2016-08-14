#include "includes.hpp"
#include "dynamicMenu.hpp"
#include "resources.hpp"
#include "menus.hpp"
#include "game.hpp"
#include "utilFunctions.hpp"
#include "textureManager.hpp"
#include "settings.hpp"

int newHighscoreScreen() {
	Menu menu;
	menu.setTitle("New Highscore");

	sf::Text Text, Prompt;

	Prompt.setFont(Font);
	Prompt.setColor(sf::Color::Red);
	Prompt.setString("Enter Your Name :");
	Prompt.setPosition(APP_WIDTH / 2 - Prompt.getGlobalBounds().width / 2,
	                   APP_HEIGHT / 2 - Prompt.getGlobalBounds().height * 3);

	Text.setFont(Font);
	Text.setPosition(APP_WIDTH / 2 - Text.getGlobalBounds().width / 2,
	                 APP_HEIGHT / 2 - Text.getGlobalBounds().height / 2);
	Text.setCharacterSize(40);
	string input;

	bool validInsert = false;

	stringstream stream;
	string name;

	while (App.isOpen() && !validInsert) {
		while (App.pollEvent (Event) ) {
			if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape)
				return 0;

			if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Return) {
				name = input;
				input.clear();
				Text.setString(input);
				Text.setPosition(APP_WIDTH / 2 - Text.getGlobalBounds().width / 2,
				                 APP_HEIGHT / 2 - Text.getGlobalBounds().height / 2);
				validInsert = true;
				}

			if (Event.type == Event.TextEntered) {
				if (Event.text.unicode == 8) {
					if (input.length() > 0) {
						input.resize(input.length() - 1);
						Text.setString(input);
						Text.setPosition(APP_WIDTH / 2 - Text.getGlobalBounds().width / 2,
						                 APP_HEIGHT / 2 - Text.getGlobalBounds().height / 2);
						}
					}
				else if (Event.text.unicode == 13) {} //No New Lines
				else {
					input += static_cast <char> (Event.text.unicode);
					//cout << Event.text.unicode << "\n";
					Text.setString(input);
					Text.setPosition(APP_WIDTH / 2 - Text.getGlobalBounds().width / 2,
					                 APP_HEIGHT / 2 - Text.getGlobalBounds().height / 2);
					}
				}

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

		menu.handle();
		App.clear();
		App.draw(Background);
		App.draw(menu);
		App.draw(Prompt);
		App.draw(Text);
		App.display();
		}

	highscores.push_back(pair<string, int>(name, gameEngine.score));
	sort(highscores.begin(), highscores.end(), [] (pair<string, int> a, pair<string, int> b) {
		return b.second < a.second;
		});
	highscores.resize(14);

	int counter = 0;
	for (auto i : highscores) {
		if (i.first == name && i.second == gameEngine.score)
			highscoresMenu(counter);
		counter++;
		}

	return -1;
	}

