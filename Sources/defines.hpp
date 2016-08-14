#ifndef DEFINES_HPP
#define DEFINES_HPP

#define VARNAME(a) #a

#define GAMENAME	"Indefinite Aeon"

#define APP_WIDTH	1920
#define APP_HEIGHT	1080
#define APP_TOP		0
#define APP_BOTTOM	APP_HEIGHT
#define APP_LEFT		0
#define APP_RIGHT	APP_WIDTH

#define BUTTONXPADDING	40
#define BUTTONYPADDING	20

#define MENU_FONT_SIZE	32

#include "settings.hpp"
#include <mutex>

extern void             *_Unwind_Resume;
extern void             *__gxx_personality_v0;

extern mutex            mtx;

extern sf::RenderWindow App;
extern sf::Event        Event;
extern sf::View         View;
extern sf::Image        Icon;

extern sf::Clock        Framerate;
extern sf::Font         Font;
extern sf::Font         CleanFont;

extern sf::Sprite Background;

extern vector <pair<string, int>> highscores;

#endif // DEFINES_HPP

