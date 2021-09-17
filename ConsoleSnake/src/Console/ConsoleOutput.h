#pragma once
#include <iostream>

class ConsoleOutput
{
	class NormalConsoleOutput;
	class WideConsoleOutput;

	public:
	static const NormalConsoleOutput Normal;
	static const WideConsoleOutput Wide;

	virtual void Write(const char* out) const = 0;
	virtual void Flush() const = 0;

	virtual const ConsoleOutput& operator<<(const char* out) const = 0;
	virtual const ConsoleOutput& operator<<(const std::string& out) const = 0;
	virtual const ConsoleOutput& operator<<(const char& out) const = 0;
	virtual const ConsoleOutput& operator<<(char&& out) const = 0;
	virtual const ConsoleOutput& operator<<(const int& out) const = 0;
	virtual const ConsoleOutput& operator<<(int&& out) const = 0;
	virtual const ConsoleOutput& operator<<(const unsigned int& out) const = 0;
	virtual const ConsoleOutput& operator<<(unsigned int&& out) const = 0;
};

class ConsoleOutput::WideConsoleOutput : public ConsoleOutput
{
	private:
	std::wostream& output = std::wcout;

	public:
	WideConsoleOutput() = default;

	void Write(const char* out) const override;
	void Flush() const override;

	const ConsoleOutput& operator<<(const char* out) const override;
	const ConsoleOutput& operator<<(const std::string& out) const override;
	const ConsoleOutput& operator<<(const char& out) const override;
	const ConsoleOutput& operator<<(char&& out) const override;
	const ConsoleOutput& operator<<(const int& out) const override;
	const ConsoleOutput& operator<<(int&& out) const override;
	const ConsoleOutput& operator<<(const unsigned int& out) const override;
	const ConsoleOutput& operator<<(unsigned int&& out) const override;
};

class ConsoleOutput::NormalConsoleOutput : public ConsoleOutput
{
	private:
	std::ostream& output = std::cout;

	public:
	NormalConsoleOutput() = default;

	void Write(const char* out) const override;
	void Flush() const override;

	const ConsoleOutput& operator<<(const char* out) const override;
	const ConsoleOutput& operator<<(const std::string& out) const override;
	const ConsoleOutput& operator<<(const char& out) const override;
	const ConsoleOutput& operator<<(char&& out) const override;
	const ConsoleOutput& operator<<(const int& out) const override;
	const ConsoleOutput& operator<<(int&& out) const override;
	const ConsoleOutput& operator<<(const unsigned int& out) const override;
	const ConsoleOutput& operator<<(unsigned int&& out) const override;
};