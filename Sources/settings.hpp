#ifndef MBINARY_SETTINGS
#define MBINARY_SETTINGS

#include "includes.hpp"

struct Settings {
	struct Graphics {
		sf::VideoMode VideoMode;
		bool fullscreenEnabled;
		bool displayFramerate;

		void restoreDefaults ();
		} graphics;

	float musicVolume;
	float soundVolume;
	bool musicEnabled;
	bool soundEnabled;

	bool save ();
	bool load () ;

	void restoreAllDefaults ();

	};

extern Settings settings;

#endif // MBINARY_SETTINGS

