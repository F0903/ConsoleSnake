#pragma once
#include "VectorSlim.h"
#include "ConsoleOutput.h"

using uint = unsigned int;

struct Controls
{
	char upKey, leftKey, downKey, rightKey;
};

struct Snake
{
	Snake(uint startX, uint startY)
		: posX(startX), posY(startY), previousX(startX), previousY(startY), tailLength(0)
	{}

	uint posX, posY;
	uint previousX, previousY;

	uint tailLength;

	char headSymbol = 'O';
	char tailSymbol = 'o';
};

struct Fruit
{
	Fruit(uint startX, uint startY, int value)
		: posX(startX), posY(startY), value(value)
	{}

	uint posX, posY;
	int value;
	char symbol = '*';
};

class SnakeGame
{
	private:
	Controls controls;
	Snake snake;
	VectorSlim<Fruit> fruits;
	int score;

	bool displayFps = true;

	ConsoleOutput* consoleOut = &ConsoleOutput::Normal;

	public:
	uint width, height;

	public:
	SnakeGame(Controls controls, uint width, uint height);

	private:
	void SetCursorPos(uint x, uint y);
	void ClearConsole();
	void SetCursor(bool visible, uint size);

	void Init();

	bool HandleInput();
	void CheckForFruitOverlap();

	void DrawGrid();
	void DrawFruits();
	void DrawSnake();
	void DrawScore();

	public:
	bool Update();

};