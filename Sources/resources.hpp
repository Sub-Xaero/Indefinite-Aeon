#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "defines.hpp"

void resourceInit ();
void setGlobalVolume ();
void instanciateWindow ();

enum RESOURCE_ERROR_CODE {
	FontError = 1,
	DataError,
	AudioError,
	GraphicsError
	};

template <typename T>
sf::Vector2f mapPixelToCoords (sf::Vector2<T> pos) {
	return App.mapPixelToCoords (sf::Vector2i (pos.x, pos.y) );
	}

sf::Vector2f mapPixelToCoords (sf::Event::MouseButtonEvent &pos);
sf::Vector2f mapPixelToCoords (sf::Event::MouseMoveEvent &pos);


#endif // RESOURCES_HPP
