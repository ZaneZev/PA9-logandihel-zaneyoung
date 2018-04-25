// PA9-logandihel-zaneyoung.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "testing.h"
#include "Game.h"

sf::RenderWindow * gameObj  = nullptr;
//extern "C"{
//	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}


int main()
{
	Game game("Nitro Knockoffs",1000,800,30);
	gameObj = &game;
	game.start();

	system("pause");
    return 0;  
}