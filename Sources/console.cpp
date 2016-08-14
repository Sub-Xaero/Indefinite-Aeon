#include "includes.hpp"
#include "defines.hpp"
#include "utilFunctions.hpp"
#include "dynamicMenu.hpp"

int console () {
	Menu menu;
	menu.setTitle ("Console");
	vector<sf::Text *> commands;
	map<string, function<void() >> commandActions = {
			{"back", [] {throw (0);}},
			{"test1", [] {}},
			{"test2", [] {}},
			{"test3", [] {}},
			{"test4", [] {}},
			{"test5", [] {}},
			{"test6", [] {}},
			{"test7", [] {}},
			{"test8", [] {}},
			{"test9", [] {}},
			{"test10", [] {}},
			{"test11", [] {}},
			{"test12", [] {}},
			{"test13", [] {}},
			{"test14", [] {}},
			{"test15", [] {}},
			{"test16", [] {}},
			{"test17", [] {}},
			{"test18", [] {}},
			{"test19", [] {}},
			{"test20", [] {}},
			{"test21", [] {}},
			{"test22", [] {}},
			{
			"help", [&] {
				stringstream s;

				for (auto i : commandActions) {
					s << i.first << ", ";
					}
				commands.push_back (new sf::Text (s.str(), Font, MENU_FONT_SIZE) );

				lineWrapText (*commands.back(), 1920);
				}
			},
		};

	sf::Text input ("-", Font, MENU_FONT_SIZE);
	input.setPosition (50, 980);

	menu.bindEvent (sf::Event::TextEntered, [&] {
		if (Event.text.unicode == 8 && input.getString().getSize() > 1) {
			string s  = input.getString().toAnsiString();
			string sub = s.substr (0, s.size() - 1);
			input.setString (input.getString().toAnsiString().erase (input.getString().toAnsiString().length() - 1) );
			}
		else if (Event.text.unicode == 13) {
			if (commands.size() == 8)
				commands.erase (commands.begin() );

			commands.push_back (new sf::Text (input.getString(), Font, MENU_FONT_SIZE) );
			input.setString ("-");
			string cmd = commands.back()->getString().toAnsiString().substr (1);

			if (commandActions.count (cmd) == 1)
				commandActions[cmd]();
			}
		else if (Event.text.unicode < 128) {
			input.setString (input.getString() + static_cast<char> (Event.text.unicode) );
			}
		});

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
		App.clear (sf::Color (100, 100, 100) );
		App.draw (menu);
		if (commands.size() > 0) {
			int y = 980;
			for (auto i = commands.rbegin(); i < commands.rend(); i++) {
				(*i)->setPosition (50, y -= 100);
				App.draw (**i);
				}
			}
		App.draw (input);
		App.display();
		}
	return -1;
	}

