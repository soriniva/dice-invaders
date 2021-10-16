#include "Utils.h"
#include "Constants.h"

#include <cassert>

bool Utils::isCompletelyOutsideScreen(const Rectangle& rectangle)
{
	return rectangle.m_x >= Engine::CanvasWidth || rectangle.m_x <= -Engine::SpriteSize ||
		rectangle.m_y >= SCREEN_Y_VISIBLE_LIMIT_DOWN || rectangle.m_y <= SCREEN_Y_VISIBLE_LIMIT_UP;
}

bool Utils::hasCollision(const Rectangle& rectangle1, const Rectangle& rectangle2)
{
	return rectangle1.m_x < rectangle2.m_x + rectangle2.m_width &&
		rectangle1.m_x + rectangle1.m_width > rectangle2.m_x &&
		rectangle1.m_y < rectangle2.m_y + rectangle2.m_height &&
		rectangle1.m_y + rectangle1.m_height > rectangle2.m_y;
}