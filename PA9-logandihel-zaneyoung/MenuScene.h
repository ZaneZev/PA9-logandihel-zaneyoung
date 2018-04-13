#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"

class MenuScene :public Scene {
public:
	MenuScene() : Scene() {
		Button * temp = new Button;
		drawables.push_back(temp);
		temp->addToDraws(drawables);
	}
};