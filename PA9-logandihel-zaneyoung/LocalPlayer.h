#pragma once
#include "testing.h"
#include <SFML/Window.hpp>
#include "Player.h"

class LocalPlayer : public Player {
public:
	LocalPlayer(sf::Vector2f pos, map *theMap, string controlls="wasd",string name = "" ) : Player(pos, name)
	{
		for (int i = 0; i < controlls.length(); i++) {
			controlls[i] -= 'a';
		}
		this->controlls = controlls;
		leftIsPressed = false;
		rightIsPressed = false;
		upIsPressed = false;
		rightIsPressed = false;
		downIsPressed = false;
		shiftIsPressed = false;

		pMap = theMap;
		setNextMarker(theMap->checkpoints.at(0));
	}

	// override
	void update();
	void updatePhysics(float dt);

	bool getLeftPressed();
	bool getRightPressed();
	bool getUpPressed();
	bool getDownPressed();
	bool getShiftPressed();

private:
	string controlls;
	void updateKeyboard();

	bool leftIsPressed;
	bool rightIsPressed;
	bool upIsPressed;
	bool downIsPressed;
	bool shiftIsPressed;
};