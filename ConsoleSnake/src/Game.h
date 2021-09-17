#pragma once
#include <vector>
#include "pch.h"
#include "Console/ConsoleOutput.h"
#include "Input/Controls.h"
#include "Snake.h"
#include "Fruit.h"
#include "Coord.h"

class Game
{
	private:
	Controls controls;
	Direction currentDirection = Direction::Up;

	Coord snakeStartPos;
	Snake snake;

	std::vector<Fruit> fruits;
	int highScore;
	int score;

	public:
	uint width, height;

	public:
	Game(Controls controls, uint width, uint height);

	private:
	void Init();

	void AddFruits(int n);
	void MoveFruit(Fruit& fruit);

	void HandleFruitCollision();
	bool CheckForGameOver();

	void HandleInput(Direction dir);
	void Move();

	void Reset();

	void DrawGrid();
	void DrawScore();
	void DrawGameOver();

	public:
	bool Update();
};