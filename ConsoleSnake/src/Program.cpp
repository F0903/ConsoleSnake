#include <fstream>
#include <string>
#include <sstream>
#include "SnakeGame.h"

int main(int argCount, const char** args)
{
	if (argCount > 0)
	{
		auto file = std::fstream("argInfo.txt", std::ios::trunc | std::ios::out);
		for (size_t i = 0; i < argCount; i++)
		{
			auto argStr = args[i];
			std::stringstream ss;
			ss << i << ". " << argStr << " \n";
			auto formattedArgStr = ss.str();
			file.write(formattedArgStr.c_str(), formattedArgStr.size());
		}
		file.close();
	}

	auto controls = Controls();
	controls.upKey = 'w';
	controls.leftKey = 'a';
	controls.downKey = 's';
	controls.rightKey = 'd';

	auto game = SnakeGame(controls, 50, 20);
	while (game.Update())
	{
	}
}