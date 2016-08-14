#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"
#include "resources.hpp"

int errorScreen ( int errorCode) {
	App.setActive(true);
	sf::RectangleShape LeftEye, RightEye, Mouth;
	LeftEye.setSize (sf::Vector2f (20, 300) );
	LeftEye.setPosition (1920 / 2 - 100, 50);

	RightEye.setSize (sf::Vector2f (20, 300) );
	RightEye.setPosition (1920 / 2 + 100, 50);

	Mouth.setSize (sf::Vector2f (300, 20) );
	Mouth.setPosition (1920 / 2 - 135, 450);

	sf::Text text ("ERROR: ", Font, MENU_FONT_SIZE),
	text2 ("Please redownload/reinstall the game.\nIf this issue continues, click here to contact support", Font, MENU_FONT_SIZE);
	text.setPosition (450, 700);
	text2.setPosition (450, 800);

	string s = "ERROR: ", reason = "";
	switch (errorCode) {
		case RESOURCE_ERROR_CODE::FontError:
			reason = "Non-Embedded Fonts Not Found/Corrupted";
			break;

		case RESOURCE_ERROR_CODE::DataError:
			reason = "Data Files Not Found/Corrupted";
			break;

		case RESOURCE_ERROR_CODE::AudioError:
			reason = "Audio Files Not Found/Corrupted";
			break;

		case RESOURCE_ERROR_CODE::GraphicsError:
			reason = "Graphics Data Not Found/Corrupted";
			break;

		default:
			reason = "Something went wrong, no idea what!";
			break;
		}
	text.setString (s + reason);
	while (App.isOpen() ) {
		while (App.pollEvent (Event) ) {
			if ( (Event.type == Event.Closed) || (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape) )
				App.close(), exit (0);
			}

		App.clear (sf::Color (150, 0, 0) );
		App.draw (LeftEye);
		App.draw (RightEye);
		App.draw (Mouth);
		App.draw (text);
		App.draw (text2);
		App.display();
		}
	return 0;
	}

