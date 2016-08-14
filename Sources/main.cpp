#include "includes.hpp"
#include "utilFunctions.hpp"
#include "Interactable.hpp"
#include "resources.hpp"
#include "save.hpp"
#include "settings.hpp"
#include "defines.hpp"
#include "menus.hpp"
#include "audio.hpp"


int main (int argc, char *argv[]) {
	srand (time (0) + rand());
	bool nosettings = false, nosplash = false;

	for (int i = 1; i < argc; i++) {
		if (string (argv[i]).find ("nosettings") != string::npos)
			nosettings = true;
		if (string (argv[i]).find ("nosplash") != string::npos)
			nosplash = true;
		}
	if (nosettings)
		settings.restoreAllDefaults();
	else settings.load();

	Icon.loadFromFile("Graphics/Icon.png");
	instanciateWindow();

	try {
		resourceInit ();
		}
	catch (int e) {
		if (!App.isOpen() ) {
			settings.graphics.VideoMode = sf::VideoMode (1920, 1080);
			if (sf::VideoMode::getFullscreenModes() [0] <= sf::VideoMode (1920, 1080) )
				settings.graphics.VideoMode = sf::VideoMode::getFullscreenModes() [0];
			instanciateWindow();
			}
		errorScreen (e);
		}

	setGlobalVolume();
	if (settings.musicEnabled && Songs.size() > 0)
		music.play();


	if (!nosplash) splashScreen();

	waitScreen();
	mainMenu();

	exit (0);
	}
