// PA9-logandihel-zaneyoung.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "testing.h"
#include "Game.h"
sf::RenderWindow * gameObj  = nullptr;
int main()
{
	Game game("Nitro Knockoffs");
	gameObj = &game;
	game.start();
    return 0;
}

