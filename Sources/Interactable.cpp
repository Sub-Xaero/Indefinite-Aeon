#include "includes.hpp"
#include "Interactable.hpp"
#include "utilFunctions.hpp"
#include "resources.hpp"
#include <iterator>

//TODO (Dylan #1 2015-08-30 ): Makeover interactable boxes to fit better with new menu system
// Make more of an interface class, daisy-chaining function calls,
// more dynamic sizing, and the ability to add buttons (Close, Action buttons) / text / custom modules
// Perhaps a cleaner font, see KCL

Interactable::Interactable (string title, float x, float y) {
	Box.setSize (sf::Vector2f (x, y) );
	Box.setFillColor (sf::Color (rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1) );
	Box.setOrigin (Box.getGlobalBounds().width / 2, Box.getGlobalBounds().height / 2);
	TitleBar.setSize (sf::Vector2f (x, 25) );
	TitleBar.setOrigin (TitleBar.getGlobalBounds().width / 2, TitleBar.getGlobalBounds().height / 2);

	int R = Box.getFillColor().r;
	int G = Box.getFillColor().g;
	int B = Box.getFillColor().b;

	TitleBar.setFillColor (sf::Color (R >= 30 ? R - 30 : 0, G >= 30 ? G - 30 : 0, B >= 30 ? B - 30 : 0) );

	TitleText.setFont (CleanFont);
	TitleText.setCharacterSize (18);
	TitleText.setString (title);
	TitleText.setStyle (sf::Text::Style::Bold);
	TitleText.setColor (sf::Color::White);
	TitleText.setOrigin (TitleText.getGlobalBounds().width / 2, TitleText.getGlobalBounds().height / 2);

	Text.setFont (CleanFont);
	Text.setCharacterSize (16);
	Text.setStyle (sf::Text::Style::Bold);
	Text.setColor (sf::Color::White);
	Text.setString ("Example Text");

	Close = TitleText;
	Close.setString ("[X]");

	this->setPosition (0, 0);
	mouseLocked = false;
	clicks = 0;
	}

Interactable &Interactable::setPosition (float x, float y) {
	TitleBar.setPosition (x, y);
	TitleText.setPosition (TitleBar.getPosition().x, TitleBar.getPosition().y);
	Box.setPosition (TitleBar.getPosition().x,
	                 TitleBar.getPosition().y + (TitleBar.getGlobalBounds().height / 2) + (Box.getGlobalBounds().height / 2) );

	Text.setPosition ( (Box.getPosition().x + 5) - Box.getOrigin().x,
	                   (Box.getPosition().y + 5) - Box.getOrigin().y);

	Close.setPosition (Box.getPosition().x - (Box.getGlobalBounds().width / 2) + 60,
	                   TitleText.getPosition().y - 5);
	return *this;
	}

sf::Vector2f Interactable::getPosition() {
	return TitleBar.getPosition();
	}

Interactable &Interactable::setTextColor (sf::Color pColour) {
	Text.setColor (pColour);
	return *this;
	}

sf::Color Interactable::getTextColor () {
	return Text.getColor();
	}

Interactable &Interactable::setColor (sf::Color pColour) {
	Box.setFillColor (pColour);
	int R = Box.getFillColor().r, G = Box.getFillColor().g, B = Box.getFillColor().b;
	TitleBar.setFillColor (sf::Color (R >= 30 ? R - 30 : 0, G >= 30 ? G - 30 : 0, B >= 30 ? B - 30 : 0) );
	return *this;
	}

sf::Color Interactable::getColor () {
	return Box.getFillColor();
	}

void Interactable::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw (Box, states);
	target.draw (TitleBar, states);
	target.draw (TitleText,  states);
	target.draw (Text, states);
	target.draw (Close, states);
	}

void InteractableEvent (sf::Event &pEvent, vector<Interactable> &boxes) {
	// Only one box is ever locked, if the mouse click is released, unlock all boxes
	if (pEvent.type == pEvent.MouseButtonReleased) for (auto ite = boxes.begin(); ite != boxes.end(); ite++) (*ite).mouseLocked = false;
	// If the mouse is pressed, loop to find the top box
	if (pEvent.type == pEvent.MouseButtonPressed) {
		for (auto ite = boxes.begin(); ite < boxes.end(); ite++) {
			// If the mouse is over the body
			if (sf::Mouse::isButtonPressed (sf::Mouse::Left)
			        && (*ite).Close.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) ) {
				bool blocked = false;
				// Iterate from the screen front to the box currently pending pickup, if there are boxes in front, it cannot be selected, block it
				for (vector<Interactable>::iterator subIte = boxes.begin(); subIte != ite; subIte++)
					if ( (*subIte).Close.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) )
						blocked = true;
				if (blocked)
					break;
				boxes.erase (ite);
				ite--;
				break; // Stop processing actions for this event
				}
			// If the mouse is over a title bar
			else if (sf::Mouse::isButtonPressed (sf::Mouse::Left)
			         && (*ite).TitleBar.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) ) {
				bool blocked = false;
				// Iterate from the screen front to the box currently pending pickup, if there are boxes in front, it cannot be selected, block it
				for (vector<Interactable>::iterator subIte = boxes.begin(); subIte != ite; subIte++)
					if ( (*subIte).Box.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) )
						blocked = true;

				if (blocked)
					break;

				// Bring it to the front of the vector and lock it
				int temp = distance (boxes.begin(), ite);
				boxes.insert (boxes.begin(), (*ite) );
				ite = boxes.begin() + temp + 1;
				boxes.front().mouseLocked = true;
				boxes.front().diff = sf::Vector2f (mapPixelToCoords (pEvent.mouseButton).x - boxes.front().getPosition().x,
				                                   mapPixelToCoords (pEvent.mouseButton).y - boxes.front().getPosition().y);
				//ite++;
				// Erase where it was in the vec
				boxes.erase (ite);
				break;
				}
			else if (sf::Mouse::isButtonPressed (sf::Mouse::Left)
			         && (*ite).Box.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) ) {
				bool blocked = false;
				// Iterate from the screen front to the box currently pending pickup, if there are boxes in front, it cannot be selected, block it
				for (vector<Interactable>::iterator subIte = boxes.begin(); subIte != ite; subIte++)
					if ( (*subIte).Box.getGlobalBounds().contains (mapPixelToCoords (pEvent.mouseButton) ) )
						blocked = true;

				if (blocked)
					break;

				(*ite).clicks++;
				(*ite).Text.setString ("Clicked " + toString ( (*ite).clicks) + " times");
				lineWrapText ( (*ite).Text, (*ite).Box.getPosition().x + ( (*ite).Box.getGlobalBounds().width / 2) - 10);
				}
			}
		}
	}

void InteractableDrawHandle (sf::RenderWindow &pApp, vector<Interactable> &boxes) {
	// Locked boxes follow the mouse here
	for (auto ite = boxes.begin(); ite != boxes.end(); ite++)
		if ( (*ite).mouseLocked)
			(*ite).setPosition (mapPixelToCoords (sf::Mouse::getPosition (App) ).x - (*ite).diff.x,
			                    mapPixelToCoords (sf::Mouse::getPosition (App) ).y - (*ite).diff.y);
	// Reverse ite, so as to display the first items in the vec last/topmost
	for (vector<Interactable>::reverse_iterator ite = boxes.rbegin(); ite != boxes.rend(); ite++) {
		pApp.draw (*ite);
		}
	}

