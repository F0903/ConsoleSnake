#include <iostream>
#include <thread>

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

void SnakeGame::Init()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	consoleOut = &ConsoleOutput::Wide;
	SetCursor(false, 1);

	for (size_t i = 0; i < 3; i++)
	{
		uint x = (uint)rand() % (width - 1);
		if (x == snake.posX)
		{
			if (x < width - 1) ++x;
			else if (x > 1) --x;
		}

		uint y = (uint)rand() % (height - 1);
		if (y == snake.posY)
		{
			if (y < height - 1) ++y;
			else if (y > 1) --y;
		}

		fruits.Instantiate(x, y, 1);
	}

	DrawGrid();
	DrawFruits();
	DrawSnake();
	DrawScore();
}

void SnakeGame::SetCursorPos(uint x, uint y)
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleOut->Flush();
	COORD coord = { x, y };
	SetConsoleCursorPosition(console, coord);
}

void SnakeGame::ClearConsole() // WIN32
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	consoleOut->Flush();

	if (!GetConsoleScreenBufferInfo(console, &csbi))
		throw "Could not retrieve console buffer info.";

	DWORD writeSize = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD count;

	FillConsoleOutputCharacter(console, TEXT(' '), writeSize, topLeft, &count);
	FillConsoleOutputAttribute(console, csbi.wAttributes, writeSize, topLeft, &count);
	SetConsoleCursorPosition(console, topLeft);
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

void SnakeGame::DrawGrid()
{
	constexpr char verticalBorderChar = '#';
	constexpr char horizontalBorderChar = '#';
	constexpr char topLeftCornerBoderChar = '#';
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

bool SnakeGame::HandleInput() // WIN32
{
	if (!_kbhit()) return false;

	snake.previousX = snake.posX;
	snake.previousY = snake.posY;

	char ch = _getch();
	if (ch == controls.upKey)
	{
		if (snake.posY == 1) return false;
		--snake.posY;
	}
	else if (ch == controls.leftKey)
	{
		if (snake.posX == 1) return false;
		--snake.posX;
	}
	else if (ch == controls.downKey)
	{
		if (snake.posY == height - 1) return false;
		++snake.posY;
	}
	else if (ch == controls.rightKey)
	{
		if (snake.posX == width - 1) return false;
		++snake.posX;
	}
	return true;
}

void SnakeGame::CheckForFruitOverlap()
{
	for (size_t i = 0; i < fruits.GetSize(); i++)
	{
		const auto& elem = fruits[i];
		if (!(elem.posX == snake.posX && elem.posY == snake.posY))
			continue;

		score += elem.value;
		++snake.tailLength;
		DrawScore();

		fruits.Remove(i);
	}
}

void SnakeGame::DrawFruits()
{
	for (size_t i = 0; i < fruits.GetSize(); i++)
	{
		const auto& elem = fruits[i];

		SetCursorPos(elem.posX, elem.posY);
		*consoleOut << elem.symbol;
	}
}

void SnakeGame::DrawSnake()
{
	SetCursorPos(snake.previousX, snake.previousY);
	*consoleOut << ' ';

	SetCursorPos(snake.posX, snake.posY);
	*consoleOut << snake.headSymbol;
}

void SnakeGame::DrawScore()
{
	auto scoreText = "score ";
	SetCursorPos((width / 2) - (strlen(scoreText) / 2), height);
	*consoleOut << scoreText << score;
}

bool SnakeGame::Update()
{
	if (HandleInput())
	{
		DrawSnake();
		CheckForFruitOverlap();
	}
	return true;
}