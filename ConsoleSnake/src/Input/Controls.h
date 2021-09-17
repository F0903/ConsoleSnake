#pragma once
#include "../pch.h"
#include "../Coord.h"

enum class Direction
{
	Up,
	Left,
	Down,
	Right,
	None
};

inline const Direction ToDirection(char ch)
{
	switch (ch)
	{
		case 'w': return Direction::Up;
		case 'a': return Direction::Left;
		case 's': return Direction::Down;
		case 'd': return Direction::Right;
		default: return Direction::None;
	}
}

struct Controls
{
	char upKey, leftKey, downKey, rightKey;
};
