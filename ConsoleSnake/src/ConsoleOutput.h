#pragma once
#include <iostream>

class ConsoleOutput
{
	class NormalConsoleOutput;
	class WideConsoleOutput;

	public:
	static NormalConsoleOutput Normal;
	static WideConsoleOutput Wide;

	virtual void Write(const char* out) = 0;
	virtual void Flush() = 0;

	virtual ConsoleOutput& operator<<(const char* out) = 0;
	virtual ConsoleOutput& operator<<(const std::string& out) = 0;
	virtual ConsoleOutput& operator<<(const char& out) = 0;
	virtual ConsoleOutput& operator<<(char&& out) = 0;
	virtual ConsoleOutput& operator<<(const int& out) = 0;
	virtual ConsoleOutput& operator<<(int&& out) = 0;
	virtual ConsoleOutput& operator<<(const unsigned int& out) = 0;
	virtual ConsoleOutput& operator<<(unsigned int&& out) = 0;
};

class ConsoleOutput::WideConsoleOutput : public ConsoleOutput
{
	private:
	std::wostream& output = std::wcout;

	public:
	WideConsoleOutput() = default;

	void Write(const char* out) override;
	void Flush() override;

	ConsoleOutput& operator<<(const char* out) override;
	ConsoleOutput& operator<<(const std::string& out) override;
	ConsoleOutput& operator<<(const char& out) override;
	ConsoleOutput& operator<<(char&& out) override;
	ConsoleOutput& operator<<(const int& out) override;
	ConsoleOutput& operator<<(int&& out) override;
	ConsoleOutput& operator<<(const unsigned int& out) override;
	ConsoleOutput& operator<<(unsigned int&& out) override;
};

class ConsoleOutput::NormalConsoleOutput : public ConsoleOutput
{
	private:
    std::ostream& output = std::cout;

	public:
	NormalConsoleOutput() = default;

	void Write(const char* out) override;
	void Flush() override;

	ConsoleOutput& operator<<(const char* out) override;
	ConsoleOutput& operator<<(const std::string& out) override;
	ConsoleOutput& operator<<(const char& out) override;
	ConsoleOutput& operator<<(char&& out) override;
	ConsoleOutput& operator<<(const int& out) override;
	ConsoleOutput& operator<<(int&& out) override;
	ConsoleOutput& operator<<(const unsigned int& out) override;
	ConsoleOutput& operator<<(unsigned int&& out) override;
};