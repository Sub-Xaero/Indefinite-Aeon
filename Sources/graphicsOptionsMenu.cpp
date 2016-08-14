#include "includes.hpp"
#include "dynamicMenu.hpp"
#include "resources.hpp"
#include "utilFunctions.hpp"
#include "settings.hpp"
#include <math.h>

int graphicsOptionsMenu() {
	Menu menu;
	menu.setTitle ("Graphics Options");

	struct Buttons {
		enum {
			Resolution,
			FullscreenToggle,
			DrawFPS,
			ApplyRes,
			Reset,
			Back,
			};
		};

	unsigned currentVideoMode;
	for (unsigned i = 0; i < settings.graphics.VideoMode.getFullscreenModes().size(); i++) {
		if (settings.graphics.VideoMode == sf::VideoMode::getFullscreenModes() [i])
			currentVideoMode = i;
		}

	double precision = 0.1;
	string aspectRatio;
		{
		int i = 2;
		double dec = ( (double) settings.graphics.VideoMode.width / (double) settings.graphics.VideoMode.height);
		while (mod (round (dec * i) - dec * i) > precision)
			i++;
		aspectRatio = " (" + toString (floor (dec * i) ) + ":" + toString (i) + ")";
		}
	menu.newButton ("Resolution : " +
	                toString (settings.graphics.VideoMode.width) + "x" +
	                toString (settings.graphics.VideoMode.height) + aspectRatio)
	.setFillColour (sf::Color::Transparent).setTextColour (sf::Color::White) = [&] {
		if (Event.mouseButton.button == sf::Mouse::Right) {
			if (currentVideoMode < sf::VideoMode::getFullscreenModes().size() - 1)
				currentVideoMode++;
			else currentVideoMode = 0;
			}

		if (Event.mouseButton.button == sf::Mouse::Left) {
			if (currentVideoMode > 0)
				currentVideoMode--;
			else currentVideoMode = sf::VideoMode::getFullscreenModes().size() - 1;
			}

			{
			int i = 2;
			double dec = ( (double) sf::VideoMode::getFullscreenModes() [currentVideoMode].width /
			(double) sf::VideoMode::getFullscreenModes() [currentVideoMode].height);

			while (mod (round (dec * i) - dec * i) > precision)
				i++;
			aspectRatio = " (" + toString (floor (dec * i) ) + ":" + toString (i) + ")";
			}

		menu[Buttons::Resolution].setString ("Resolution : " +
		toString (sf::VideoMode::getFullscreenModes() [currentVideoMode].width) + "x" +
		toString (sf::VideoMode::getFullscreenModes() [currentVideoMode].height) + aspectRatio);
		};

	menu.newButton ("Fullscreen : " + toString (settings.graphics.fullscreenEnabled) ).mimicStyles (menu[Buttons::Resolution]) = [&] {
		settings.graphics.fullscreenEnabled = !settings.graphics.fullscreenEnabled;
		menu[Buttons::FullscreenToggle].setString ("Fullscreen : " + toString (settings.graphics.fullscreenEnabled) );
		instanciateWindow();
		};

	menu.newButton ("Draw FPS : " + toString (settings.graphics.displayFramerate) ).mimicStyles (menu[Buttons::Resolution]) = [&] {
		settings.graphics.displayFramerate = !settings.graphics.displayFramerate;
		menu[Buttons::DrawFPS].setString ("Draw FPS : " + toString (settings.graphics.displayFramerate) );
		};

	menu.newButton ("Apply Resolution", 730, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) ).mimicStyles (menu[Buttons::Resolution]) = [&] {
		if (settings.graphics.VideoMode != sf::VideoMode::getFullscreenModes() [currentVideoMode]) {
			settings.graphics.VideoMode = sf::VideoMode::getFullscreenModes() [currentVideoMode];
			instanciateWindow();
			}
		};

	menu.newButton ("Reset", 1700, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) ).mimicStyles (menu[Buttons::Resolution]) = [&] {
		settings.graphics.restoreDefaults();
		instanciateWindow();
			{
			int i = 2;
			double dec = ( (double) settings.graphics.VideoMode.width / (double) settings.graphics.VideoMode.height);
			while (mod (round (dec * i) - dec * i) > precision)
				i++;
			aspectRatio = " (" + toString (floor (dec * i) ) + ":" + toString (i) + ")";
			}
		menu[Buttons::Resolution].setString ("Resolution : " +
		toString (settings.graphics.VideoMode.width) + "x" +
		toString (settings.graphics.VideoMode.height) + aspectRatio
		                                    );
		menu[Buttons::FullscreenToggle].setString ("Fullscreen : " + toString (settings.graphics.fullscreenEnabled) );
		};

	menu.newButton ("Back", 50, 1080 - (Font.getLineSpacing (MENU_FONT_SIZE * 2 + 20) ) ).mimicStyles (menu[Buttons::Resolution]) = [&] {throw (0);};

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
		App.display();
		}
	return -1;
	}

