#include "Snake.h"
#include "Renderer.h"

void Snake::InitTail(const Coord startCoord)
{
	parts.emplace_back(startCoord); // Head
	parts.emplace_back(startCoord); // End
}

void Snake::Move(const Coord& to)
{
	for (int i = length + 1; i > 0; i--)
	{
		const auto& nextPos = parts[i - 1];
		parts[i] = nextPos;
	}

	auto& head = parts[0];
	head = to;
}

void Snake::AddTailPart()
{
	parts.push_back(GetHead());
	++length;
}

void Snake::ClearTail(const Coord resetPoint)
{
	parts.clear();
	length = 0;
	InitTail(resetPoint);
}

void Snake::Draw() const
{
	Renderer::Draw(' ', GetEnd());

	for (size_t i = 1; i <= length; i++)
	{
		const auto& part = parts[i];
		Renderer::Draw(tailSymbol, part);
	}

	Renderer::Draw(headSymbol, GetHead());
}