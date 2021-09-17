#pragma once
#include "pch.h"

struct Fruit
{
	Fruit(uint startX, uint startY, int value = 1)
		: posX(startX), posY(startY), value(value)
	{}

	uint posX, posY;
	int value;
	char symbol = '*';
};