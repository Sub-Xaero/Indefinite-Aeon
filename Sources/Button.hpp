#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "includes.hpp"

using namespace std;

extern sf::Font Font;

struct Button : public sf::Drawable {
	private :
		sf::Text text;
		sf::Text subText;
		sf::RectangleShape button;

		virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		function <void() > action;

		void operator() ();
		void operator= (function<void() > pAction);

		Button &mimicStyles (Button &pButton);
		Button &setAction (function<void() > pAction);
		sf::FloatRect getGlobalBounds ();

		Button &setFillColour (sf::Color colour);
		sf::Color getFillColour ();

		Button &setFontSize (int fSize);
		int getFontSize ();

		Button &setOutlineColour (sf::Color colour);
		sf::Color getOutlineColour ();

		Button &setOutlineThickness (float px);
		float getOutlineThickness ();

		Button &setString (string S);
		string getString ();

		Button &setTextColour (sf::Color colour);
		sf::Color getTextColour ();

		Button &setPosition (sf::Vector2f pos);
		sf::Vector2f getPosition ();

		template <typename T> bool contains (T x, T y) {
			return button.getGlobalBounds().contains (x, y);
			}

		Button ();
	};


#endif // BUTTON_HPP
