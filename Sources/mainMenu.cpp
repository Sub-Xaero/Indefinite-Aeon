#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "utilFunctions.hpp"
#include "menus.hpp"
#include "save.hpp"
#include "game.hpp"
#include "version.hpp"

int mainMenu() {
	Menu menu;
	menu.bindEvent (sf::Event::KeyPressed, [&] {if (Event.key.code == sf::Keyboard::Key::Escape) App.close(), saveAndQuit();});

	menu.setTitle(GAMENAME);
	menu.newButton ("New Game")
	.setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White) = [&] {menu.subMenuEntered = true; game();};
#ifdef DEVMODE
	menu.newButton ("Dev Tools").mimicStyles (menu[0]) = [] {devMenu();};
#endif // DEVMODE
	menu.newButton ("Highscores").mimicStyles (menu[0]) = [&] {highscoresMenu();};
	menu.newButton ("Options").mimicStyles (menu[0]) = [&] {optionsMenu();};
	menu.newButton ("Credits").mimicStyles (menu[0]) = [&] {creditsMenu();};
	menu.newButton ("Quit").mimicStyles (menu[0]) = [&] {App.close(), saveAndQuit(), throw (0);};

	sf::Text versionText (string(AutoVersion::STATUS) + " Version : " + string(AutoVersion::FULLVERSION_STRING), CleanFont, 25);
	versionText.setColor(sf::Color::White);
	versionText.setStyle(sf::Text::Bold);
	versionText.setPosition(APP_RIGHT - versionText.getGlobalBounds().width - 10,
	                        APP_BOTTOM - versionText.getGlobalBounds().height - 10);

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
		App.draw (Background);
		App.draw (menu);
		App.draw (versionText);
		App.display();
		}
	return 0;
	}

