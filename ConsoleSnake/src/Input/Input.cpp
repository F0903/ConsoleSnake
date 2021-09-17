#include "Input.h"
#include <conio.h>

std::vector<Input::OnInputFunc> Input::onInput;

void Input::CheckInput()
{
	//TODO: Use win32 to check instead of getch
	if (!_kbhit()) return;
	char ch = static_cast<char>(_getch());
	const auto& funcs = Input::onInput;
	for (size_t i = 0; i < funcs.size(); i++)
	{
		funcs[i](ToDirection(ch));
	}
}

void Input::SubToInput(OnInputFunc&& func)
{
	Input::onInput.push_back(std::forward<OnInputFunc>(func));
}
