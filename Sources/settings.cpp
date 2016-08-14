#include "settings.hpp"
#define SETTINGSFILE "Save/Settings"

bool Settings::save () {
	fstream file (SETTINGSFILE, fstream::out | fstream::binary);
	if (file)
		file.write ( (char *) this, (sizeof (Settings) ) );
	else return false;
	file.close();
	return true;
	};

bool Settings::load () {
	fstream file (SETTINGSFILE, fstream::in | fstream::binary);
	if (file) {
		file.read ( (char *) this, (sizeof (Settings) ) );
		if (sf::VideoMode::getFullscreenModes() [0] < graphics.VideoMode)
			graphics.VideoMode = sf::VideoMode::getFullscreenModes() [0];
		}
	else {
		restoreAllDefaults();
		return false;
		}
	file.close();
	return true;
	};

void Settings::restoreAllDefaults () {
	//NOTE Settings Defaults Here
	graphics.restoreDefaults();
	musicVolume = 100;
	soundVolume = 100;
	musicEnabled = true;
	soundEnabled = true;
	};

void Settings::Graphics::restoreDefaults() {
	//NOTE Graphics Defaults Here
	VideoMode = sf::VideoMode (1920, 1080);
	displayFramerate = false;
	if (sf::VideoMode::getFullscreenModes() [0] <= sf::VideoMode (1920, 1080) )
		VideoMode = sf::VideoMode::getFullscreenModes() [0];
	fullscreenEnabled = true;
	};

