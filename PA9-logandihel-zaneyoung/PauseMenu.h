#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "Button.h"
#include <SFML\Graphics.hpp>

class PauseMenu : public sf::Drawable {
public:
	PauseMenu(sf::View *viewRef, sf::Font &font) : Drawable() {
		this->viewRef = viewRef;
		background = nullptr;
		background = new sf::RectangleShape();
		background->setFillColor(sf::Color(0,0,0,127));
		background->setOutlineColor(sf::Color::Black);
		background->setOutlineThickness(5);
		message = new sf::Text("Pause\n\nPress Q to Quit\nPress SPACE to Resume", font);
		resize();
		isRendered = false;
	}

	virtual ~PauseMenu() {
		delete background;
		delete message;
	}

	void resize() {
		background->setSize(viewRef->getSize()/2.f + sf::Vector2f(40,0));
		background->setPosition(viewRef->getCenter() - viewRef->getSize()/2.f + viewRef->getSize()/4.f);

		message->setPosition(background->getPosition());
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		if (isRendered) {
			target.draw(*background);
			target.draw(*message);
		}
	}

	void setMessage(string message) {
		this->message->setString(message);
	}

public:
	sf::RectangleShape *background;
	sf::View *viewRef;
	sf::Text *message;
	bool isRendered;
};
#endif