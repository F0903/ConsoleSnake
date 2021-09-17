#pragma once
#include <functional>
#include <vector>
#include "../pch.h"
#include "Controls.h"

class Input
{
	public:
	using OnInputFunc = std::function<void(Direction dir)>;

	private:
	static std::vector<OnInputFunc> onInput;

	public:
	static void CheckInput();
	static void SubToInput(OnInputFunc&& onInput);
};

