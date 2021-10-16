#pragma once

#include "Rectangle.h"

class Utils
{
public:
	static bool isCompletelyOutsideScreen(const Rectangle& rectangle);

	static bool hasCollision(const Rectangle& rectangle1, const Rectangle& rectangle2);
};