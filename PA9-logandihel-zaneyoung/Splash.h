#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>
class SplashScreen : public sf::Drawable{
public:
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const {
		sf::Font font;
		sf::Text text("HELLO WORLD AND THINGS...", font);
		text.setCharacterSize(30);
		text.setColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		target.draw(text);

	}
};