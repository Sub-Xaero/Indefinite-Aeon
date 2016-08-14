#include "includes.hpp"
#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"
#include "utilFunctions.hpp"

int highscoresMenu (int highlight) {
	Menu menu;
	menu.setTitle ("Highscores");
	menu.newButton ("Back", 50, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) )
	.setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White) = [] {throw (0);};

	vector<sf::Text> scoreTexts;
		{
		int creditSize = 28;

		highscores.resize(14);
		int counter = 0;
		for (auto i : highscores) {
			scoreTexts.push_back (sf::Text (padStringSpaces(trimStringLength(i.first, 50), 50) + " " + toString(i.second), Font, creditSize) );
			if (counter == highlight)
				scoreTexts.back().setColor(sf::Color::Green);
			counter++;
			}

		int y = 200;
		for (auto i = scoreTexts. begin(); i != scoreTexts.end(); i++)
			(*i).setPosition (50, y),
			(*i).setStyle (sf::Text::Style::Bold),
			y += Font.getLineSpacing ( (*i).getCharacterSize() + 5);
		}
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
		menu.handle();
		App.clear();
		App.draw (Background);
		App.draw (menu);
		for (auto i : scoreTexts) App.draw (i);
		App.display();
		}
	return -1;
	}


