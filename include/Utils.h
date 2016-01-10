#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>

namespace sf
{
	class Sprite;
	class Text;
}

void CenterOrigin(sf::Sprite & sprite);
void CenterOrigin(sf::Text & text);
std::string toString(sf::Keyboard::Key key);