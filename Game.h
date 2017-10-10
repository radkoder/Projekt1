#pragma once
#include <array>

#include "uFunctionStorage.h"
#include "uResource.h"
#include "uDisplayManager.h"
#include "uInputHandler.h"
#include "uDisplayObject.h"
/*
temporary Game class for testing purposes.

*/
class Game
{
public:

	Game()
	{
		//Get viewport dismensions
		SDL_GetCurrentDisplayMode(0, &displayInfo);
	}
	
	void load()
	{
		
		int Padding = 25;
		int RowHeight = procentH(7);
		int ColWidth = procentW(7);

		//display grid of invaders
		for (size_t i = 0; i < invaders.size(); i++)
		{
			for (size_t j = 0; j < invaders[i].size(); j++)
			{
				switch (i)
				{
				case 0:
				case 1:
					invaders[i][j].setImage("res/SPACEC1.png");
					break;
				case 2:
				case 3:
					invaders[i][j].setImage("res/SPACEB1.png");
					break;
				case 4:
				case 5:
					invaders[i][j].setImage("res/SPACEA1.png");
					break;
				}
				invaders[i][j].setWH(ColWidth - 10, RowHeight - 10);
				invaders[i][j].setXY((j + 1)*(ColWidth + Padding), (i + 1)*(RowHeight + Padding));
				utl::uDisplayManager::loadObject(&invaders[i][j]);
			}
		}

		//Initialise other display objects
		player.setImage("res/PLAYER.png");
		utl::uDisplayManager::loadObject(&player);
		player.setXY(invaders.front().back().getTarget()->x, invaders.back().back().getTarget()->y + procentH(20));

		laser.setImage("res/BOOM.png");
		laser.setTarget(*(player.getTarget()));
		laser.active = false;
		utl::uDisplayManager::loadObject(&laser);

		//define keymappings
		handler.on(SDL_KEYDOWN, SDLK_LEFT, [this]() {
			player.setXY(player.getTarget()->x - 10, player.getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_RIGHT, [this]() {
			player.setXY(player.getTarget()->x + 10, player.getTarget()->y);
		});

		handler.on(SDL_KEYDOWN, SDLK_ESCAPE, [this]() {
			quit = true;
		});

		handler.on(SDL_KEYDOWN, SDLK_SPACE, [this]() {
			shoot();
		});

	}

	void tick()
	{
		handler.processKeyboard();
	}
	void shoot()
	{
		laser.active = true;
		if (laser.getTarget()->y <= 0)
		{
			laser.active = false;
			laser.setTarget(*(player.getTarget()));
		}
		laser.setXY(laser.getTarget()->x, laser.getTarget()->y - 10);
	}

	int procentW(int x)
	{
		std::clamp(x, 0, 100);
		float onePercent = displayInfo.w / 100.0f;
		return (int)onePercent * x;
	};
	int procentH(int x)
	{
		std::clamp(x, 0, 100);
		float onePercent = displayInfo.h / 100.0f;
		return (int)onePercent * x;
	};

	std::array<std::array<utl::uDisplayObject, 11>, 6> invaders;
	utl::uDisplayObject player;
	utl::uDisplayObject laser;
	bool quit = false;
	utl::uInputHandler handler;
	SDL_DisplayMode displayInfo;


	/*void setRowHeight(int newVal)
	{
	RowHeight = newVal;
	for (auto&& rows : invaders)
	{
	for (auto&& invs : rows)
	invs.setWH(ColWidth, RowHeight);
	}
	}
	void setColWidth(int newVal)
	{
	ColWidth = newVal;
	for (auto&& rows : invaders)
	{
	for (auto&& invs : rows)
	invs.setWH(ColWidth, RowHeight);
	}
	}*/
};