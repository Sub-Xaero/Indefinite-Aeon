#ifndef PROGRESSMODULE_HPP
#define PROGRESSMODULE_HPP

#include <functional>
#include <thread>
#include "defines.hpp"

struct ProgressCircle {

	private:
		double Radius;
		double Angle;
		double progressDegrees;
		int Separation;

		sf::Vector2f Position;
		sf::VertexArray ProgressBar;
		sf::Color Colour;

	public:
		ProgressCircle();

		void draw (sf::RenderWindow &Window);

		ProgressCircle &setSize (float pRadius);
		float getSize ();

		ProgressCircle &setSeparation (int Sep);
		int	getSeparation ();

		ProgressCircle &setPosition (sf::Vector2f Pos);
		sf::Vector2f getPosition();

		ProgressCircle &setPercentage (float percentage);
		float getPercentage ();

		ProgressCircle &setColor (sf::Color newColour);
		sf::Color getColor ();


	};

struct ProgressBar {

	private:
		double Percentage;

		sf::RectangleShape Outline;
		sf::RectangleShape Bar;

	public:
		ProgressBar();
		ProgressBar (sf::Vector2f size);

		void draw (sf::RenderWindow &Window);
		ProgressBar &setSize (sf::Vector2f size);
		sf::Vector2f getSize();

		ProgressBar &setPosition (sf::Vector2f Pos);
		sf::Vector2f getPosition();

		ProgressBar &setBarColor (sf::Color newColour);
		sf::Color getBarColor ();

		ProgressBar &setBackgroundColor (sf::Color newColour);
		sf::Color getBackgroundColor ();

		ProgressBar &setOutlineColor (sf::Color newColour);
		sf::Color getOutlineColor ();

		ProgressBar &setPercentage (double percentage);
		float getPercentage ();

	};

void saveLoadScreen (string Text, function <bool (int &progress) > procedure);

#endif // PROGRESSMODULE_HPP
