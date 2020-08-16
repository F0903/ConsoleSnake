#include "ConsoleOutput.h"

ConsoleOutput::NormalConsoleOutput ConsoleOutput::Normal;
ConsoleOutput::WideConsoleOutput ConsoleOutput::Wide;


void ConsoleOutput::WideConsoleOutput::Write(const char* out)
{
	output << out;
}

void ConsoleOutput::WideConsoleOutput::Flush()
{
	output.flush();
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const char* out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const std::string& out)
{
	output << out.c_str();
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const char& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(char&& out)
{
	output << out;
	return *this;
}


ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const int& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(int&& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(const unsigned int& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::WideConsoleOutput::operator<<(unsigned int&& out)
{
	output << out;
	return *this;
}



void ConsoleOutput::NormalConsoleOutput::Write(const char* out)
{
	output << out;
}

void ConsoleOutput::NormalConsoleOutput::Flush()
{
	output.flush();
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const char* out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const std::string& out)
{
	output << out.c_str();
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const char& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(char&& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const int& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(int&& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(const unsigned int& out)
{
	output << out;
	return *this;
}

ConsoleOutput& ConsoleOutput::NormalConsoleOutput::operator<<(unsigned int&& out)
{
	output << out;
	return *this;
}