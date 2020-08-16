#pragma once
#include "VectorSlim.h"
#include "ConsoleOutput.h"

using uint = unsigned int;

enum class Direction
{
	Up,
	Left,
	Down,
	Right
};

struct Controls
{
	char upKey, leftKey, downKey, rightKey;
};

struct Coord
{
	Coord(uint x, uint y) : x(x), y(y) {}
	uint x, y;
};

struct Snake
{
	Snake(uint startX, uint startY)
		: pos(startX, startY)
	{
		// The top one is needed due to the end link occupying the same space as the next. This is a temp solution
		tailPositions.Instantiate(startX, startY); // First Link
		tailPositions.Instantiate(startX, startY); // End of tail.
	}

	Coord pos;

	VectorSlim<Coord> tailPositions = VectorSlim<Coord>();

	char headSymbol = 'O';
	char tailSymbol = 'o';
};

struct Fruit
{
	Fruit(uint startX, uint startY, int value = 1)
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
	Direction currentDirection = Direction::Up;
	Snake snake;
	VectorSlim<Fruit> fruits;
	int score;

	bool displayFps = false;

	ConsoleOutput* consoleOut = &ConsoleOutput::Normal;

	public:
	uint width, height;

	public:
	SnakeGame(Controls controls, uint width, uint height);

	private:
	void SetCursorPos(Coord coords);
	void SetCursor(bool visible, uint size);

	void AddTail();
	void AddFruits(int n);
	void MoveFruit(Fruit& fruit);
	void Init();

	void HandleInput();
	void CheckForFruitOverlap();
	bool CheckForGameOver();

	void Reset();

	void DrawGrid();
	void DrawSnake();
	void DrawScore();
	void DrawGameOver();

	public:
	bool Update();

};