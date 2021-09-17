#include <Windows.h>
#include "Renderer.h"

const ConsoleOutput& Renderer::consoleOut = ConsoleOutput::Wide;

void Renderer::SetCursorPos(Coord coords) noexcept
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleOut.Flush();
	COORD winCoords = { static_cast<SHORT>(coords.x), static_cast<SHORT>(coords.y) };
	SetConsoleCursorPosition(console, winCoords);
}

void Renderer::SetCursor(bool visible, uint size) noexcept // WIN32
{
	static const auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(console, &info);
	info.bVisible = visible;
	info.dwSize = size;
	SetConsoleCursorInfo(console, &info);
}

inline void Renderer::Write(const char ch) noexcept
{
	consoleOut << ch;
}

inline void Renderer::Write(const std::string& str) noexcept
{
	consoleOut << str;
}

void Renderer::Draw(const char ch, const Coord at) noexcept
{
	SetCursorPos(at);
	Write(ch);
}

void Renderer::Draw(const std::string& str, const Coord at) noexcept
{
	SetCursorPos(at);
	Write(str);
}