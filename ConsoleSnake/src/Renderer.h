#pragma once
#include <string>
#include "pch.h"
#include "Console/ConsoleOutput.h"
#include "Coord.h"

class Renderer
{
	private:
	static const ConsoleOutput& consoleOut;

	private:
	static void SetCursorPos(Coord coords) noexcept;
	static void Write(const char ch) noexcept;
	static void Write(const std::string& str) noexcept;

	public:
	static void SetCursor(bool visible, uint size) noexcept;
	static void Draw(const char ch, const Coord at) noexcept;
	static void Draw(const std::string& str, const Coord at) noexcept;

	friend class Game;
};

