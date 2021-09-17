#include <iostream>
#include <thread>
#include <sstream>

// WIN32
#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include "pch.h"
#include "Game.h"
#include "Renderer.h"
#include "Input/Input.h"

using namespace std::chrono_literals;

//TODO: Refactor into classes

Game::Game(Controls controls, uint width, uint height)
	: snakeStartPos(width / 2, height / 2), snake(snakeStartPos), controls(controls), width(width), height(height)
{
	Init();
}

void Game::AddFruits(int n)
{
	const auto& pos = snake.GetHead();
	for (size_t i = 0; i < n; i++)
	{
		uint x = (uint)rand() % (width - 1);
		if (x == width - 1) --x;
		if (x == 0) ++x;
		if (x == pos.x)
		{
			if (pos.x == 1) ++x;
			else --x;
		}

		uint y = (uint)rand() % (height - 1);
		if (y == height - 1) --y;
		if (y == 0) ++y;
		if (y == pos.y)
		{
			if (pos.y == 1) ++y;
			else --y;
		}

		const auto& fruit = fruits.emplace_back(x, y);

		Renderer::Draw(fruit.symbol, { fruit.posX, fruit.posY });
	}
}

void Game::MoveFruit(Fruit& fruit)
{
	const auto& pos = snake.GetHead();
	uint x = (uint)rand() % (width - 1);
	if (x == width - 1) --x;
	if (x == 0) ++x;
	if (x == pos.x)
	{
		if (pos.x == 1) ++x;
		else --x;
	}

	uint y = (uint)rand() % (height - 1);
	if (y == height - 1) --y;
	if (y == 0) ++y;
	if (y == pos.y)
	{
		if (pos.y == 1) ++y;
		else --y;
	}

	fruit.posX = x;
	fruit.posY = y;
	Renderer::Draw(fruit.symbol, { fruit.posX, fruit.posY });
}

void Game::Reset()
{
	system("cls"); // WIN32
	DrawGrid();

	currentDirection = Direction::Up;
	if (score > highScore)
		highScore = score;
	score = 0;

	snake.Move(snakeStartPos);
	snake.ClearTail(snakeStartPos);

	fruits.clear();
	AddFruits((width + height) / 10);
}

void Game::DrawGrid()
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
				Renderer::Write(horizontalBorderChar);
				continue;
			}

			if (x == 0 || x == width)
			{
				Renderer::Write(verticalBorderChar);
				continue;
			}

			Renderer::Write(' ');
		}
		Renderer::Write('\n');
	}
}

void Game::Move()
{
	auto pos = snake.GetHead();
	switch (currentDirection)
	{
		case Direction::Up:
			pos.y -= 1;
			break;
		case Direction::Left:
			pos.x -= 1;
			break;
		case Direction::Down:
			pos.y += 1;
			break;
		case Direction::Right:
			pos.x += 1;
			break;
		default:
			break;
	}
	snake.Move(pos);
}

void Game::HandleFruitCollision()
{
	const auto& pos = snake.GetHead();
	for (size_t i = 0; i < fruits.size(); i++)
	{
		auto& elem = fruits[i];
		if (!(elem.posX == pos.x && elem.posY == pos.y))
			continue;

		score += elem.value;
		MoveFruit(elem);
		DrawScore();
		snake.AddTailPart();
	}
}

bool Game::CheckForGameOver()
{
	const auto& pos = snake.GetHead();
	if (pos.x == 0 || pos.x == width)
		return true;

	if (pos.y == 0 || pos.y == height)
		return true;

	for (size_t i = 1; i <= snake.GetLength(); i++)
	{
		const auto tailPiece = snake.GetTailPart(static_cast<uint>(i));
		if (pos.x == tailPiece.x && pos.y == tailPiece.y)
			return true;
	}

	return false;
}

void Game::DrawScore()
{
	std::stringstream scoreText;
	scoreText << "|SCORE " << score << "|";
	auto scoreStr = scoreText.str();
	Renderer::Draw(scoreStr, { (width / 2) - (static_cast<uint>(scoreStr.size()) / 2), height });
}

void Game::DrawGameOver()
{
	system("cls"); // WIN32
	std::stringstream gameOverText;
	gameOverText << "GAME OVER\n"
		<< "High Score: " << highScore << '\n'
		<< "Final Score: " << score
		<< "\n\nPress any button to continue...";
	Renderer::Draw(gameOverText.str(), { 0, 0 });
}

void Game::HandleInput(Direction dir)
{
	if (dir == Direction::None) return;
	if (static_cast<int>(dir) == static_cast<int>(currentDirection) - 2) return;
	if (static_cast<int>(dir) == static_cast<int>(currentDirection) + 2) return;
	currentDirection = dir;
}

void Game::Init()
{
	const auto _ = _setmode(_fileno(stdout), _O_U16TEXT);
	Renderer::SetCursor(false, 1);

	DrawGrid();
	AddFruits((width + height) / 10);
	DrawScore();
	Input::SubToInput([this](Direction dir) { HandleInput(dir); });
}

bool Game::Update()
{
	Input::CheckInput();
	Move();
	snake.Draw();
	if (CheckForGameOver())
	{
		DrawGameOver();
		while (!_getch()) { std::this_thread::sleep_for(250ms); }
		Reset();
		return true;
	}
	HandleFruitCollision();
	std::this_thread::sleep_for(100ms);
	return true;
}