#pragma once
#include "Scene.h"
#include "SplashScreen.h"

class SplashScene : public Scene {
public:
	SplashScene() : Scene() {
		drawables.push_back(new SplashScreen());
	}
};