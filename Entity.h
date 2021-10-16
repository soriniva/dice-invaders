#pragma once

#include "Engine.h"
#include "Rectangle.h"
#include <memory>

class Entity
{
public:
	Entity(std::shared_ptr<Engine> engine)
		: m_engine(engine)
	{
	}

	virtual void draw() = 0;
	virtual void update(float dt) = 0;
	virtual void handleCollision() = 0;
	virtual void checkCollision(std::shared_ptr<Entity> entity) {}

	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
	bool isVisible() const { return m_isVisible; }
	const Rectangle& getBoundingBox() const { return m_boundingBox; }
	void updateBoundingBoxPos(float xOffset, float yOffset)
	{
		m_boundingBox.m_x = m_posX + xOffset;
		m_boundingBox.m_y = m_posY + yOffset;
	}

protected:
	bool m_isVisible = true;
	std::shared_ptr<Engine> m_engine = nullptr;
	int m_speed = 0;
	float m_posX = 0;
	float m_posY = 0;
	Rectangle m_boundingBox;
};
