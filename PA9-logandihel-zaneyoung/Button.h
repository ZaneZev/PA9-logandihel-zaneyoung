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
class Button :public sf::Drawable{
public:
	Button(sf::Color unPressedColor, sf::Color pressedColor,sf::Color hoverColor, string btnText, sf::Vector2f location,sf::Vector2f size,int id):Drawable(){
		ID = id;
		this->unPressedColor = unPressedColor;
		this->pressedColor = pressedColor;
		this->hoverColor = hoverColor;
		this->rect = new sf::RectangleShape(location);
		this->rect->setSize(size);
		rect->setFillColor(unPressedColor);
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(10);
		setText(btnText);
		clicked = false;
	}
	Button(string btnText,int id):Drawable() {

		ID = id;
		this->rect = new sf::RectangleShape(sf::Vector2f(0.0f,0.0f));
		this->rect->setSize(sf::Vector2f(1000, 200));
		this->rect->setPosition(sf::Vector2f(200, 200));
		unPressedColor = sf::Color::Blue;
		pressedColor = sf::Color(200, 200, 200, 255);
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		rect->setFillColor(unPressedColor);
		text = new sf::Text();
		text->setColor(sf::Color::Red);
		text->setFont(font);
		text->setCharacterSize(30);
		setText(btnText);
		clicked = false;
	}
	~Button() {
		delete text;
		delete rect;
	}
	void setText(string newText) {
		text->setString(newText);
		updateTextPos();
	}
	bool checkMouse(sf::Vector2i mousePos,bool leftClick) {
		if (checkMousePos(mousePos)&&leftClick) {
			cout << "ID : " << ID << " Mouse In , ?clicked , click" << endl;
			if (clicked == false) {
				clicked = true;
				rect->setFillColor(pressedColor);
			}
			return false;
		}
		if (leftClick && clicked) {
			cout << "ID : " << ID << " Mouse out , clicked , click" << endl;
			clicked = false;
			rect->setFillColor(unPressedColor);
			return false;
		}
		if (checkMousePos(mousePos) && !leftClick&&clicked) {
			cout << "ID : " << ID << " Mouse In , !clicked , click" << endl;
			rect->setFillColor(unPressedColor);
			return true;
		}
		if (checkMousePos(mousePos)) {
			cout << "THE MOUSE IS IN!" << endl;
			return false;
		}
		cout << "ID : " << ID << " hit no Ifs"<<endl;
		return false;
	}
	bool checkMousePos(sf::Vector2i mousePos) {

		if (mousePos.x >rect->getPosition().x && mousePos.x < rect->getPosition().x + rect->getLocalBounds().width) {
			if (mousePos.y > rect->getPosition().y && mousePos.y < rect->getPosition().y + rect->getLocalBounds().height) {
				return true;
			}
		}
		return false;
	}
	bool isClicked() {
		return clicked;
	}
	int getId() {
		return ID;
	}
	void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(*rect, states);
		target.draw(*text, states);
	}
private:
	sf::RectangleShape * rect;
	bool clicked;
	int ID;
	sf::Font font;
	sf::Text *text;
	sf::Color unPressedColor;
	sf::Color pressedColor;
	sf::Color hoverColor;

	//updates the position of the text inside of the rectangle, should happen automatically any time the text changes or the button position is changed
	void updateTextPos() {
		text->setPosition(sf::Vector2f(this->rect->getPosition().x + ((this->rect->getLocalBounds().width / 2) - (text->getLocalBounds().width / 2)), this->rect->getPosition().y + ((this->rect->getLocalBounds().height / 2) - (text->getLocalBounds().height / 2))));
	}
};