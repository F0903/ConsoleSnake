#include "ConsoleOutput.h"

const ConsoleOutput::NormalConsoleOutput ConsoleOutput::Normal;
const ConsoleOutput::WideConsoleOutput ConsoleOutput::Wide;

void ConsoleOutput::WideConsoleOutput::Write(const char* out) const
{
	output << out;
}

void ConsoleOutput::WideConsoleOutput::Flush() const
{
	output.flush();
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const char* out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const std::string& out) const
{
	output << out.c_str();
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const char& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(char&& out) const
{
	output << out;
	return *this;
}


const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const int& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(int&& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const unsigned int& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(unsigned int&& out) const
{
	output << out;
	return *this;
}



void ConsoleOutput::NormalConsoleOutput::Write(const char* out) const
{
	output << out;
}

void ConsoleOutput::NormalConsoleOutput::Flush() const
{
	output.flush();
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const char* out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const std::string& out) const
{
	output << out.c_str();
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const char& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(char&& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const int& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(int&& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const unsigned int& out) const
{
	output << out;
	return *this;
}

const ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(unsigned int&& out) const
{
	output << out;
	return *this;
}