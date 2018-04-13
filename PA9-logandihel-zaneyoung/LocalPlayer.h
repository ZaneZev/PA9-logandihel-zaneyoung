#pragma once
#include "testing.h"
#include <SFML/Window.hpp>
#include "Player.h"

class LocalPlayer : public Player {
public:
	LocalPlayer(string name = "") : Player(name) 
	{
		leftIsPressed = false;
		rightIsPressed = false;
		upIsPressed = false;
		rightIsPressed = false;
		downIsPressed = false;
		shiftIsPressed = false;
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
	void updateKeyboard();

	bool leftIsPressed;
	bool rightIsPressed;
	bool upIsPressed;
	bool downIsPressed;
	bool shiftIsPressed;
};