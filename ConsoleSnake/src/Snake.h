#pragma once
#include <vector>
#include "pch.h"
#include "Coord.h"

class Snake
{
	public:
	Snake(const Coord startCoord)
	{
		InitTail(startCoord);
	}

	private:
	static constexpr char headSymbol = 'O';
	static constexpr char tailSymbol = 'o';

	std::vector<Coord> parts;
	uint length = 0;

	private:
	void InitTail(const Coord startCoord);
	const Coord GetEnd() const { return parts[parts.size() - 1]; }

	public:
	const uint GetLength() const { return length; }

	const Coord GetTailPart(const uint i) const
	{
		if (i > length) throw;
		return parts[i];
	}

	const Coord GetHead() const { return parts[0]; }

	void Move(const Coord& to);
	void AddTailPart();
	void ClearTail(const Coord resetPoint);
	void Draw() const;
};