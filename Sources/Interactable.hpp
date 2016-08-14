#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <functional>

struct Interactable : public sf::Drawable {
		sf::RectangleShape TitleBar;
		sf::RectangleShape Box;
		sf::Text TitleText;
		sf::Text Text;
		sf::Text Close;
		bool mouseLocked;
		int clicks;
		sf::Vector2f diff;

		function <void (void) > handler;

		Interactable (string title, float x, float y);

		Interactable &setPosition (float x, float y);
		Interactable &setPosition (sf::Vector2f);
		sf::Vector2f getPosition();

		Interactable &setColor (sf::Color);
		sf::Color getColor ();

		Interactable &setTextColor (sf::Color);
		sf::Color getTextColor ();

	private:
		virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
	};

void InteractableEvent (sf::Event &pEvent, vector<Interactable> &boxes);
void InteractableDrawHandle (sf::RenderWindow &pApp, vector<Interactable> &boxes);

#endif // INTERACTABLE_HPP

