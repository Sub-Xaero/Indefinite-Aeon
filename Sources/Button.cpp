#include "Button.hpp"
#include "defines.hpp"

void Button::draw (sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw (button, states);
	target.draw (text, states);
	target.draw (subText, states);
	}

void Button::operator() () {
	action();
	}

void Button::operator= (function<void() > pAction) {
	action = pAction;
	}

Button &Button::mimicStyles (Button &pButton) {
	setTextColour (pButton.getTextColour() );
	setFillColour (pButton.getFillColour() );
	setOutlineColour (pButton.getOutlineColour() );
	return *this;
	}

Button &Button::setAction (function<void() > pAction) {
	action = pAction;
	return *this;
	}

Button &Button::setFillColour (sf::Color colour) {
	button.setFillColor (colour);
	return *this;
	}

Button &Button::setFontSize (int fSize) {
	text.setCharacterSize (fSize);
	subText.setCharacterSize (fSize);
	button.setSize (sf::Vector2f (text.getGlobalBounds().width + BUTTONXPADDING, text.getGlobalBounds().height + BUTTONYPADDING) );
	return *this;
	}

Button &Button::setOutlineColour (sf::Color colour) {
	button.setOutlineColor (colour);
	return *this;
	}

Button &Button::setOutlineThickness (float px) {
	button.setOutlineThickness (px);
	return *this;
	}

Button &Button::setString (string S) {
	text.setString (S);
	button.setSize (sf::Vector2f (text.getGlobalBounds().width + BUTTONXPADDING, text.getGlobalBounds().height + BUTTONYPADDING) );
	return *this;
	}

Button &Button::setTextColour (sf::Color colour) {
	text.setColor (colour);
	subText.setColor (colour);
	return *this;
	}

Button &Button::setPosition (sf::Vector2f pos) {
	button.setPosition (pos);
	text.setPosition (button.getPosition().x + (BUTTONXPADDING / 2), button.getPosition().y + (BUTTONYPADDING * 0.2) );
	subText.setPosition (text.getPosition().x + text.getGlobalBounds().width + 20, text.getPosition().y);
	return *this;
	}

sf::Color Button::getFillColour () {
	return button.getFillColor();
	}

sf::Color Button::getOutlineColour () {
	return button.getOutlineColor();
	}

float Button::getOutlineThickness () {
	return button.getOutlineThickness();
	}

string Button::getString () {
	return text.getString();
	}

sf::Color Button::getTextColour () {
	return text.getColor();
	}

sf::Vector2f Button::getPosition () {
	return button.getPosition();
	}

sf::FloatRect Button::getGlobalBounds() {
	return button.getGlobalBounds();
	}


Button::Button () {
	text.setFont (Font);
	text.setStyle (sf::Text::Style::Bold);
	setString ("Hello there");
	setTextColour (sf::Color::White);
	setFontSize (MENU_FONT_SIZE);
	setPosition (sf::Vector2f (100, 100) );
	setFillColour (sf::Color::Blue);
	setOutlineColour (sf::Color::Green);
	subText = text;
	subText.setPosition (text.getPosition().x + text.getGlobalBounds().width + 20, text.getPosition().y);
	subText.setString ("");
	action = [] {};
	}


