#ifndef GAME_HPP
#define GAME_HPP

#include <iterator>
#include <algorithm>
#include <functional>
#include <thread>
#include <string>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

#include "progressModule.hpp"
#include "resources.hpp"
#include "utilFunctions.hpp"
#include "includes.hpp"
#include "defines.hpp"
#include "save.hpp"
#include "planets.hpp"
#include "alien.hpp"
#include "ship.hpp"
#include "explosion.hpp"

struct GameEngine : public sf::Drawable {
	void init();
	void runHandles();
	vector <function<void()>> handlers;

	//double version;
	bool gameQuit = false, gameOver = false;

	sf::Clock gameClock;

	sf::Clock FPSDisplayTimeout;
	sf::Clock regenClock;
	sf::Clock planetClock;
	sf::Clock alienClock;

	sf::Text FPSDisplay;
	sf::Text scoreDisplay;
	sf::Text healthDisplay;

	int score;
	int spawnAmount = 1;

	vector<sf::RectangleShape> particles;
	vector<Planet> planets;
	vector<Explosion> explosions;
	vector<Alien> aliens;
	vector<sf::RectangleShape> playerBullets;
	vector<sf::RectangleShape> alienBullets;


	Ship player;

	virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
	};

extern GameEngine gameEngine;

int game ();

#endif // GAME_HPP

