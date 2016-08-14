#include "game.hpp"
#include "menus.hpp"
#include "audio.hpp"

void GameEngine::init() {
	gameQuit = gameOver = false;

	player.Sprite.setTexture (textureManager["Blue Ship"]);
	player.Sprite.setPosition(APP_WIDTH / 2 - player.Sprite.getGlobalBounds().width / 2, APP_HEIGHT - player.Sprite.getGlobalBounds().height);
	player.health = player.maxHealth;
	player.damage = 25;
	player.level = 1;
	sf::Mouse::setPosition((sf::Vector2i)mapPixelToCoords(player.Sprite.getPosition()), App);

	gameClock.restart();
	FPSDisplayTimeout.restart();
	planetClock.restart();
	alienClock.restart();

	score = 0;
	spawnAmount = 1;

	planets.clear();
	particles.clear();
	aliens.clear();
	handlers.clear();
	playerBullets.clear();
	alienBullets.clear();
	explosions.clear();

	healthDisplay.setFont(CleanFont);
	healthDisplay.setCharacterSize(MENU_FONT_SIZE);
	healthDisplay.setString("Health: ");
	healthDisplay.setPosition(10, APP_HEIGHT - healthDisplay.getGlobalBounds().height - 10);

	scoreDisplay = healthDisplay;
	scoreDisplay.setString("Score : 0");
	scoreDisplay.setPosition(APP_WIDTH - scoreDisplay.getGlobalBounds().width - 10, APP_HEIGHT - scoreDisplay.getGlobalBounds().height - 10);

	FPSDisplay = sf::Text ("30", Font, MENU_FONT_SIZE * 1.2);
	FPSDisplay.setPosition (APP_WIDTH - FPSDisplay.getGlobalBounds().width - 10, 10);

	planets.push_back(Planet());
	aliens.push_back(Alien());
	aliens.push_back(Alien());
	aliens.push_back(Alien());


	for (int i = 0; i < 50; i++) {
		particles.push_back(sf::RectangleShape(sf::Vector2f(1, 1)));
		auto &j = particles.back();
		j.setPosition(rand() % APP_WIDTH, rand() % APP_HEIGHT);
		}

	// FPS
	handlers.push_back([&] {
		if (settings.graphics.displayFramerate && FPSDisplayTimeout.getElapsedTime().asSeconds() > 0.5) {
			FPSDisplay.setString (toString ( (int) (1.0 / Framerate.getElapsedTime().asSeconds() ) ) );
			FPSDisplay.setPosition (APP_WIDTH - FPSDisplay.getGlobalBounds().width - 10, 10);
			FPSDisplayTimeout.restart();
			}
		Framerate.restart();
		});

	// PARTICLES
	handlers.push_back([&] {
		int explosionCount = 0;
		for (auto &i : explosions) {
			i.Sprite.rotate(3);
			i.Sprite.scale(1.001, 1.001);
			i.Sprite.setColor(sf::Color(i.Sprite.getColor().r, i.Sprite.getColor().g, i.Sprite.getColor().b, i.Sprite.getColor().a - 20));
			if (i.Sprite.getColor().a <= 20)
				explosions.erase(explosions.begin() + explosionCount);
			else
				explosionCount++;
			}
		});

	// PARTICLES
	handlers.push_back([&] {
		for (int i = 0; i < 5; i++) {
			particles.push_back(sf::RectangleShape(sf::Vector2f(1, 1)));
			auto &j = particles.back();
			j.setPosition(rand() % APP_WIDTH, 0);
			}
		int particleCount = 0;
		for (auto &i : particles) {
			i.move(0, (rand() % 3) * 10);
			if (i.getPosition().y > APP_HEIGHT)
				particles.erase(particles.begin() + particleCount);
			else
				particleCount++;
			}
		});

	// PLANETS
	handlers.push_back([&] {
		if (planetClock.getElapsedTime().asSeconds() > 30) {
			if (rand() % 2 == 1)
				planets.push_back(Planet());
			planetClock.restart();
			}

		int planetCount = 0;
		for (auto &i : planets) {
			i.Sprite.move(0, 1);
			if (i.leftRotate)
				i.Sprite.rotate(-0.3);
			else
				i.Sprite.rotate(0.3);
			if (i.Sprite.getPosition().y > APP_HEIGHT)
				planets.erase(planets.begin() + planetCount);
			else
				planetCount++;
			}
		});

	// ALIENS
	handlers.push_back([&] {
		spawnAmount = ((int)gameClock.getElapsedTime().asSeconds() / 60) + 1;

		if (alienClock.getElapsedTime().asSeconds() > 6) {
			for (int i = 0; i < spawnAmount; i++)
				aliens.push_back(Alien());
			alienClock.restart();
			}

		int alienCount = 0;
		for (auto &alien : aliens) {
			if (alien.shootClock.getElapsedTime().asSeconds() > alien.shotRate) {
				alien.shootClock.restart();
				alienBullets.push_back(sf::RectangleShape(sf::Vector2f(5, 10)));
				auto &bullet = alienBullets.back();
				bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2 );
				bullet.setPosition(alien.Sprite.getPosition());
				bullet.setFillColor(sf::Color::Red);
				if (settings.soundEnabled && soundManager.count("shot") != 0)
					soundManager["shot"].second.play();
				}
			alien.Sprite.move(rand() % 3 - 1, 1);
			if (alien.Sprite.getPosition().y > APP_HEIGHT) {
				aliens.erase(aliens.begin() + alienCount);
				gameOver = true;
				}
			else
				alienCount++;
			}

		});

	// PLAYER BULLETS
	handlers.push_back([&] {
		int bulletCount = 0;
		for (auto &bullet : playerBullets) {
			bool deallocate = false;
			bullet.move(0, -10);
			int alienCount = 0;
			for (auto &thisAlien : aliens) {
				if (thisAlien.Sprite.getGlobalBounds().intersects(bullet.getGlobalBounds())) {
					deallocate = true;
					thisAlien.health -= player.damage;
					if (settings.soundEnabled && soundManager.count("hitmarker") != 0)
						soundManager["hitmarker"].second.play();
					if (thisAlien.health <= 0) {

						scoreDisplay.setString("Score : " + toString(score += thisAlien.maxHealth));
						scoreDisplay.setPosition(APP_WIDTH - scoreDisplay.getGlobalBounds().width - 10,
						APP_HEIGHT - scoreDisplay.getGlobalBounds().height - 10);

						explosions.push_back(Explosion(thisAlien.Sprite.getPosition()));
						aliens.erase(aliens.begin() + alienCount);
						aliens.push_back(Alien());

						if (settings.soundEnabled && soundManager.count("explosion") != 0)
							soundManager["explosion"].second.play();
						}
					}
				else
					alienCount++;
				}

			if (bullet.getPosition().y <= 0 || deallocate)
				playerBullets.erase(playerBullets.begin() + bulletCount);
			else
				bulletCount++;
			}
		});

	// ALIEN BULLETS
	handlers.push_back([&] {
		int bulletCount = 0;

		for (auto &i : alienBullets) {
			bool deallocate = false;
			i.move(0, 10);
			if (player.Sprite.getGlobalBounds().intersects(i.getGlobalBounds())) {
				player.health -= 5;
				deallocate = true;
				}

			if (i.getPosition().y > APP_HEIGHT || deallocate)
				alienBullets.erase(alienBullets.begin() + bulletCount);
			else
				bulletCount++;
			}
		});

	// PLAYER
	handlers.push_back([&] {
		if (regenClock.getElapsedTime().asSeconds() > 1 && player.health < 100) {
			regenClock.restart();
			player.health++;
			}

		if (score != 0 && player.level == 1 && score >= 10000 && score < 20000) {
			player.level++;
			player.damage *= 2;
			player.Sprite.setTexture(textureManager["Red Ship"]);
			}

		if (score != 0 && player.level == 2 && score >= 20000 && score < 30000) {
			player.level++;
			player.damage *= 2;
			player.Sprite.setTexture(textureManager["Pointy Ship"]);
			}

		if (score != 0 && player.level == 3 && score >= 30000 && score < 40000) {
			player.level++;
			player.damage *= 2;
			player.Sprite.setTexture(textureManager["Tropical Ship"]);
			}

		if (score != 0 && player.level == 4 && score >= 40000 && score < 50000) {
			player.level++;
			player.damage *= 2;
			player.Sprite.setTexture(textureManager["Green Ship"]);
			}

		if (player.health <= 0)
			gameOver = true;

		double animDelay = 0.2;
		if (player.moving && player.moveClock.getElapsedTime().asSeconds() < animDelay) {
			if (player.Sprite.getTextureRect() == sf::IntRect(0, 0, 100, 100))
				player.Sprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
			}
		else if (player.moving && player.moveClock.getElapsedTime().asSeconds() >= animDelay) {
			player.moving = false;
			if (player.Sprite.getTextureRect() == sf::IntRect(100, 0, 100, 100))
				player.Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
			}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		player.shootClock.getElapsedTime().asSeconds() > 0.09 &&
		gameClock.getElapsedTime().asSeconds() > 0.3) {
			player.shootClock.restart();
			playerBullets.push_back(sf::RectangleShape(sf::Vector2f(5, 10)));
			auto &i = playerBullets.back();
			i.setOrigin(i.getGlobalBounds().width / 2, i.getGlobalBounds().height / 2 );
			i.setPosition(player.Sprite.getPosition());
			i.setFillColor(sf::Color::Cyan);
			if (settings.soundEnabled && soundManager.count("shot") != 0)
				soundManager["shot"].second.play();
			}

		healthDisplay.setString("Health : " + toString(player.health));
		});

	}

void GameEngine::runHandles() {
	for (auto i : handlers)
		i();
	}

void GameEngine::draw( sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw (healthDisplay, states);
	target.draw (scoreDisplay, states);

	for (auto &i : particles)
		target.draw (i, states);

	for (auto &i : planets)
		target.draw (i, states);

	for (auto &i : alienBullets)
		target.draw (i, states);

	for (auto &i : playerBullets)
		target.draw (i, states);

	for (auto &i : explosions)
		target.draw (i, states);

	for (auto &i : aliens)
		target.draw (i, states);

	target.draw (player, states);

	if (settings.graphics.displayFramerate)
		target.draw(FPSDisplay, states);
	}

int game () {
	gameEngine.init();
	App.setMouseCursorVisible(false);

	map <sf::Event::EventType, function<void (void) >> gameEvents = {
			{
			Event.Closed,
			[&] {
				saveAndQuit();
				}
			},
			{
			Event.MouseMoved,
			[&] {
				if (Event.mouseMove.x > APP_LEFT && Event.mouseMove.x < APP_RIGHT) {
					gameEngine.player.Sprite.setPosition(mapPixelToCoords(Event.mouseMove).x, mapPixelToCoords(Event.mouseMove).y);
					gameEngine.player.moveClock.restart();
					gameEngine.player.moving = true;
					}
				}
			},
			{
			Event.KeyPressed,
			[&] {
				if (Event.key.code == sf::Keyboard::Escape) {
					App.setMouseCursorVisible(true);
					pauseMenu();
					if (gameEngine.gameQuit)
						throw (-1);
					App.setMouseCursorVisible(false);
					}
				}
			}
		};

	while (App.isOpen() ) {
		while (App.pollEvent (Event) ) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && gameEvents.count ( (sf::Event::EventType) i) == 1) {
					try {
						gameEvents[Event.type]();
						}
					catch (int p) {
						return 0;
						}
					}
				}
			}
		gameEngine.runHandles();

		if (gameEngine.gameOver) {
			App.setMouseCursorVisible(true);
			gameOverScreen();
			return -1;
			}

		App.clear();
		App.draw (Background);
		App.draw(gameEngine);
		App.display();
		}
	return -1;
	}
