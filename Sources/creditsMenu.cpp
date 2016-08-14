#include "includes.hpp"
#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"

int creditsMenu () {
	Menu menu;
	menu.setTitle ("Credits");
	menu.newButton ("Back", 50, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) )
	.setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White) = [] {throw (0);};

	vector<sf::Text> Credits;
		{
		int creditSize = 20;
		Credits.push_back (sf::Text ("Dylan Clarke:", Font, creditSize) );
		Credits.push_back (sf::Text ("- Music: DJ Striden", Font, creditSize) );
		Credits.push_back (sf::Text ("- Graphics, Hand Drawn and Processed with Adobe Illustrator CC", Font, creditSize) );
		Credits.push_back (sf::Text ("- Coded in C++11, using Code::Blocks OpenSource IDE and MinGW", Font, creditSize) );
		Credits.push_back (sf::Text ("", Font, creditSize) );
		Credits.push_back (sf::Text ("Other Resources:", Font, creditSize) );
		Credits.push_back (sf::Text ("- SFML, by Laurent Gomilla (http://www.sfml-dev.org/)", Font, creditSize) );
		Credits.push_back (sf::Text ("- Cereal, C++11 Serialization (http://uscilab.github.io/cereal)", Font, creditSize) );
		Credits.push_back (sf::Text ("- Sound Effects from Various Free Sound Banks", Font, creditSize) );
		Credits.push_back (sf::Text ("- Feedback, Code-Breaking and Moral Support, by Gregory Jensen", Font, creditSize) );
		Credits.push_back (sf::Text ("- All Resources Used Under Opens License(s) or with the express", Font, creditSize) );
		Credits.push_back (sf::Text ("  permission of the intellectual owner(s)", Font, creditSize) );
		Credits.push_back (sf::Text ("", Font, creditSize) );
		Credits.push_back (sf::Text ("A proof of concept that ended up actually being quite fun, ", Font, creditSize) );
		Credits.push_back (sf::Text ("this game is the product of a love of programming and retro style games,", Font, creditSize) );
		Credits.push_back (sf::Text ("many failed attempts, refined and recycled ideas, hundreds of", Font, creditSize) );
		Credits.push_back (sf::Text ("gallons of coffee, heartless scrutiny and hours of insanity.", Font, creditSize) );
		Credits.push_back (sf::Text ("... Never give up <3", Font, creditSize) );

		int y = 200;
		for (auto i = Credits. begin(); i != Credits.end(); i++)
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
		for (auto i : Credits) App.draw (i);
		App.display();
		}
	return -1;
	}

