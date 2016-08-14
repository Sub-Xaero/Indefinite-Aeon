#ifdef DEVMODE

#include "defines.hpp"
#include "utilFunctions.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"
#include "person.hpp"
#include "company.hpp"
#include "console.hpp"
#include "interactable.hpp"

int devMenu () {
	Menu menu;
	menu.setTitle ("Developer Menu");
	vector<sf::Text *> InfoText;
	vector<Interactable> interactables;

	struct Buttons {
		enum {
			ActionButton,
			ScrollLeft,
			ScrollRight,
			Back
			};
		};

	enum Options {
		GeneratePerson = 1,
		Console,
		MakeWindow,
		GenerateCompany,
		};

	int option = Options::GeneratePerson;

	menu.newButton ("Generate Person", 700, 300).setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White);
	menu.newButton ("<", menu[Buttons::ActionButton].getPosition().x - 150, 300).mimicStyles (menu[Buttons::ActionButton]) = [&] {
		if (option > 1)
			option--;
		else option = GenerateCompany;
		};

	menu.newButton (">", menu[Buttons::ActionButton].getPosition().x + menu[Buttons::ActionButton].getGlobalBounds().width + 50, 300).mimicStyles (menu[Buttons::ActionButton])  = [&] {
		if (option < GenerateCompany) option++;
		else option = 1;
		};

	menu.newButton ("Back", 50, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) ).mimicStyles (menu[Buttons::ActionButton]) = [&] {throw (0);};

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
			InteractableEvent (Event, interactables);
			}
		switch (option) {
			case GeneratePerson:
				menu[Buttons::ActionButton].setString ("Generate Person") = [&] {
					if (InfoText.size() > 0)
						InfoText.clear();

					Person person;
					InfoText.push_back (new sf::Text ("Name: " + person.name, Font, MENU_FONT_SIZE) );
					InfoText.push_back (new sf::Text ("ID  : " + person.ID, Font, MENU_FONT_SIZE) );
					InfoText.push_back (new sf::Text ("IBAN: " + person.IBAN, Font, MENU_FONT_SIZE) );
					};

				menu[Buttons::ScrollRight].setPosition (sf::Vector2f (menu[Buttons::ActionButton].getPosition().x + menu[Buttons::ActionButton].getGlobalBounds().width + 50, 300) );
				break;

			case Console:
				menu[Buttons::ActionButton].setString ("Console") = [&] {
					if (InfoText.size() > 0)
						InfoText.clear();
					console();
					};
				menu[Buttons::ScrollRight].setPosition (sf::Vector2f (menu[Buttons::ActionButton].getPosition().x + menu[Buttons::ActionButton].getGlobalBounds().width + 50, 300) );
				break;

			case MakeWindow:
				menu[Buttons::ActionButton].setString ("New Window") = [&] {
					if (InfoText.size() > 0)
						InfoText.clear();
					interactables.push_back (Interactable ("Window " + toString (rand() % 100 + 1), 500, 200) );

					if (interactables.size() > 1)
						interactables.back().setPosition (interactables[interactables.size() - 2].getPosition().x + 50, 500);
					else interactables.back().setPosition (500, 500);
					};
				menu[Buttons::ScrollRight].setPosition (sf::Vector2f (menu[Buttons::ActionButton].getPosition().x + menu[Buttons::ActionButton].getGlobalBounds().width + 50, 300) );
				break;

			case GenerateCompany:
				menu[Buttons::ActionButton].setString ("Generate Company") = [&] {
					if (InfoText.size() > 0) InfoText.clear();
					InfoText.push_back (new sf::Text ("Name: " + generateCompanyName(), Font, MENU_FONT_SIZE) );
					};
				menu[Buttons::ScrollRight].setPosition (sf::Vector2f (menu[Buttons::ActionButton].getPosition().x + menu[Buttons::ActionButton].getGlobalBounds().width + 50, 300) );
				break;

			}
		menu.handle();
		App.clear();
		App.draw (Background);
		if (InfoText.size() > 0 ) {
			int y = 350;
			for (auto i : InfoText) {
				(*i).setPosition (675, y += 100);
				(*i).setStyle (sf::Text::Bold);
				(*i).setColor (sf::Color::Green);
				App.draw (*i);
				}
			}
		App.draw (menu);
		InteractableDrawHandle (App, interactables);
		App.display();
		}
	return -1;
	}

#endif // DEVMODE
