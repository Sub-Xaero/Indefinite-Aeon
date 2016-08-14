#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Button.hpp"

using namespace std;

struct Menu : public sf::Drawable {
	public:
		bool suppressTitle = false;
		bool subMenuEntered;

		vector <sf::RectangleShape> particles;

		vector <Button *> buttonManager;
		map <sf::Event::EventType, function<void() >> eventManager;

		sf::Text Title;
		sf::Text TitleUnderline;

		Menu ();

		void setTitle (string s);

		Button &newButton (string Title, float x, float y);
		Button &newButton (string Title);

		void bindEvent (sf::Event::EventType, function<void() > pAction);
		void bindEvents (map <sf::Event::EventType, function<void() >> pList);

		void hover ();

		string getTitle ();

		Button &operator [] (int i);

		void handle();
	private:
		virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

		sf::Clock FPSDisplayTimeout;
		sf::Text FramerateDisplay;
	};

#endif // MENU_HPP

