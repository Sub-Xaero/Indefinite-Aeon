#include "includes.hpp"
#include "defines.hpp"
#include "settings.hpp"
#include "game.hpp"

void             *_Unwind_Resume;
void             *__gxx_personality_v0;

mutex            mtx;

sf::RenderWindow App;
sf::Event        Event;
sf::View         View;
sf::Image        Icon;

sf::Clock        Framerate;
sf::Font         Font;
sf::Font         CleanFont;

Settings         settings;
GameEngine       gameEngine;

sf::Sprite       Background;

vector <pair<string, int>> highscores;
