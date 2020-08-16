#include <iostream>
#include <thread>
#include <sstream>

// WIN32
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include <conio.h>

#include "SnakeGame.h"

using namespace std::chrono_literals;

SnakeGame::SnakeGame(Controls controls, uint width, uint height)
	: snake(width / 2, height / 2), controls(controls), width(width), height(height)
{
	Init();
}

void SnakeGame::AddTail()
{
	snake.tailPositions.Add(snake.pos);
}

void SnakeGame::AddFruits(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		uint x = (uint)rand() % (width - 1);
		if (x == width - 1) --x;
		if (x == 0) ++x;
		if (x == snake.pos.x)
		{
			if (snake.pos.x == 1) ++x;
			else --x;
		}

		uint y = (uint)rand() % (height - 1);
		if (y == height - 1) --y;
		if (y == 0) ++y;
		if (y == snake.pos.y)
		{
			if (snake.pos.y == 1) ++y;
			else --y;
		}

		const auto& fruit = fruits.Instantiate(x, y);
		SetCursorPos(Coord(fruit.posX, fruit.posY));
		*consoleOut << fruit.symbol;
	}
}

void SnakeGame::MoveFruit(Fruit& fruit)
{
	uint x = (uint)rand() % (width - 1);
	if (x == width - 1) --x;
	if (x == 0) ++x;
	if (x == snake.pos.x)
	{
		if (snake.pos.x == 1) ++x;
		else --x;
	}

	uint y = (uint)rand() % (height - 1);
	if (y == height - 1) --y;
	if (y == 0) ++y;
	if (y == snake.pos.y)
	{
		if (snake.pos.y == 1) ++y;
		else --y;
	}

	fruit.posX = x;
	fruit.posY = y;
	SetCursorPos(Coord(fruit.posX, fruit.posY));
	*consoleOut << fruit.symbol;
}

void SnakeGame::Init()
{
	auto _ = _setmode(_fileno(stdout), _O_U16TEXT);
	consoleOut = &ConsoleOutput::Wide;
	SetCursor(false, 1);

	DrawGrid();
	AddFruits((width + height) / 10);
	DrawSnake();
	DrawScore();
}

void SnakeGame::SetCursorPos(Coord coords)
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleOut->Flush();
	COORD winCoords = { coords.x, coords.y };
	SetConsoleCursorPosition(console, winCoords);
}

void SnakeGame::SetCursor(bool visible, uint size) // WIN32
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(console, &info);
	info.bVisible = visible;
	info.dwSize = size;
	SetConsoleCursorInfo(console, &info);
}

void SnakeGame::Reset()
{
	system("cls"); // WIN32
	DrawGrid();
	snake.pos = Coord(width / 2, height / 2);
	
	snake.tailPositions.Clear();
	snake.tailPositions.Add(snake.pos); // Comments in the header to why this is neccesary
	snake.tailPositions.Add(snake.pos);

	currentDirection = Direction::Up;
	score = 0;

	fruits.Clear();
	AddFruits((width + height) / 10);
}

void SnakeGame::DrawGrid()
{
	// #######
	// #     #
	// #     #
	// #######
	constexpr char verticalBorderChar = '#';
	constexpr char horizontalBorderChar = '#';
	for (size_t y = 0; y <= height; y++)
	{
		for (size_t x = 0; x <= width; x++)
		{
			if (y == 0 || y == height)
			{
				*consoleOut << horizontalBorderChar;
				continue;
			}

			if (x == 0 || x == width)
			{
				*consoleOut << verticalBorderChar;
				continue;
			}

			*consoleOut << ' ';
		}
		*consoleOut << '\n';
	}
}

void SnakeGame::HandleInput()
{
	snake.tailPositions[0] = Coord(snake.pos.x, snake.pos.y);
	for (size_t i = snake.tailPositions.GetSize() - 1; i > 0; i--)
		snake.tailPositions[i] = snake.tailPositions[i - 1];

	if (_kbhit()) // WIN32
	{
		char ch = _getch();
		if (ch == controls.upKey && currentDirection != Direction::Down)
			currentDirection = Direction::Up;
		else if (ch == controls.leftKey && currentDirection != Direction::Right)
			currentDirection = Direction::Left;
		else if (ch == controls.downKey && currentDirection != Direction::Up)
			currentDirection = Direction::Down;
		else if (ch == controls.rightKey && currentDirection != Direction::Left)
			currentDirection = Direction::Right;
	}

	switch (currentDirection)
	{
		case Direction::Up:
			--snake.pos.y;
			break;

		case Direction::Left:
			--snake.pos.x;
			break;

		case Direction::Down:
			++snake.pos.y;
			break;

		case Direction::Right:
			++snake.pos.x;
			break;

		default:
			break;
	}
}

void SnakeGame::CheckForFruitOverlap()
{
	for (size_t i = 0; i < fruits.GetSize(); i++)
	{
		auto& elem = fruits[i];
		if (!(elem.posX == snake.pos.x && elem.posY == snake.pos.y))
			continue;

		score += elem.value;
		MoveFruit(elem);
		AddTail();

		DrawScore();
	}
}

bool SnakeGame::CheckForGameOver()
{
	if (snake.pos.x == 0 || snake.pos.x == width)
		return true;

	if (snake.pos.y == 0 || snake.pos.y == height)
		return true;

	/*for (size_t i = 4; i < snake.tailPositions.GetSize(); i++)
	{
		const auto& elem = snake.tailPositions[i];
		if (snake.pos.x == elem.x && snake.pos.y == elem.y)
			return true;
	}*/
	return false;
}

void SnakeGame::DrawSnake()
{
	SetCursorPos(snake.pos);
	*consoleOut << snake.headSymbol;

	for (size_t i = 0; i < snake.tailPositions.GetSize(); i++)
	{
		auto coord = snake.tailPositions[i];
		SetCursorPos(coord);
		if (i == snake.tailPositions.GetSize() - 1)
			*consoleOut << ' ';
		else
			*consoleOut << snake.tailSymbol;
	}
}

void SnakeGame::DrawScore()
{
	std::stringstream scoreText;
	scoreText << "|SCORE " << score << "|";
	auto scoreStr = scoreText.str();
	SetCursorPos(Coord((width / 2) - (scoreStr.size() / 2), height));
	*consoleOut << scoreStr;
}

void SnakeGame::DrawGameOver()
{
	system("cls"); // WIN32
	SetCursorPos(Coord(0, 0));
	*consoleOut << "GAME OVER\n" << "Final Score: " << score << "\n\nPress any button to continue...";
}

bool SnakeGame::Update()
{
	if (!CheckForGameOver())
	{
		HandleInput();
		DrawSnake();
		CheckForFruitOverlap();
		std::this_thread::sleep_for(100ms);
	}
	else
	{
		DrawGameOver();
		while (!_getch()) { std::this_thread::sleep_for(250ms); }
		Reset();
	}
	return true;
}