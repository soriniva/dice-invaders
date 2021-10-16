#include "Weapon.h"
#include "Utils.h"
#include "Constants.h"

#include <iostream>

Weapon::Weapon(std::shared_ptr<Engine> engine, Type type, float posX, float posY, int speed)
	: Entity(engine)
	, m_type(type)
{
	init(posX, posY);
	if (m_type == Type::Bomb)
	{
		m_sprite = Engine::Sprite::Bomb;
		m_yDirection = 1.f;
		m_boundingBox = { m_posX, m_posY, BOMB_WIDTH, BOMB_HEIGHT };
		m_boundingBoxXOffset = BOMB_BB_X_OFFSET;
		m_boundingBoxYOffset = BOMB_BB_Y_OFFSET;
	}
	else if (m_type == Type::Rocket)
	{
		m_sprite = Engine::Sprite::Rocket;
		m_yDirection = -1.f;
		m_boundingBox = { m_posX, m_posY, ROCKET_WIDTH, ROCKET_HEIGHT };
		m_boundingBoxXOffset = ROCKET_BB_X_OFFSET;
		m_boundingBoxYOffset = ROCKET_BB_Y_OFFSET;
	}
	else
	{
		std::cerr << "Invalid weapon type" << std::endl;
	}

	m_speed = speed;
}

void Weapon::init(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;
	m_isVisible = true;
}

void Weapon::draw()
{
	if (!m_isVisible)
	{
		return;
	}

	m_engine->drawSprite(
		m_sprite,
		(int)m_posX, (int)m_posY);
}

void Weapon::update(float dt)
{
	if (!m_isVisible)
	{
		return;
	}

	m_posY += static_cast<float>(m_speed) * m_yDirection * dt;
	
	updateBoundingBoxPos(m_boundingBoxXOffset, m_boundingBoxYOffset);

	if (Utils::isCompletelyOutsideScreen(getBoundingBox()))
	{
		m_isVisible = false;
	}
}

void Weapon::handleCollision()
{
	m_isVisible = false;
}