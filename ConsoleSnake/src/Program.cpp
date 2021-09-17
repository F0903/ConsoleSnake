#include <fstream>
#include <string>
#include <sstream>
#include "pch.h"
#include "Game.h"
#include "Input/Controls.h"

int main()
{
	auto controls = Controls();
	controls.upKey = 'w';
	controls.leftKey = 'a';
	controls.downKey = 's';
	controls.rightKey = 'd';

	auto game = Game(controls, 50, 20);
	while (game.Update())
	{
	}
}