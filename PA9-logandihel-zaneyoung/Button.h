#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <iostream>
#include <vector>
using std::string;
class Button :public sf::RectangleShape{
public:
	Button(sf::Color unPressedColor, sf::Color pressedColor, string btnText, sf::Vector2f location,sf::Vector2f size):RectangleShape(){
		this->unPressedColor = unPressedColor;
		this->pressedColor = pressedColor;
		this->setPosition(location);
		this->setSize(size);
		setFillColor(unPressedColor);
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(50);
		text->setString(btnText);
		updateTextPos();
	}
	Button():RectangleShape() {
		unPressedColor = sf::Color::White;
		pressedColor = sf::Color(200, 200, 200, 255);
		setFillColor(unPressedColor);
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(50);
		text->setString("PLACE HOLDER");
		updateTextPos();
	}
	~Button() {}
	void setText(string newText) {
		text->setString(newText);
		updateTextPos();
	}
private:
	sf::Font font;
	sf::Text *text;
	sf::Color unPressedColor;
	sf::Color pressedColor;

	//updates the position of the text inside of the rectangle, should happen automatically any time the text changes or the button position is changed
	void updateTextPos() {
		text->setPosition(sf::Vector2f(this->getPosition().x + ((this->getLocalBounds().width / 2) - (text->getLocalBounds().width / 2)), this->getPosition().y + ((this->getLocalBounds().height / 2) - (text->getLocalBounds().height / 2))));
	}
};