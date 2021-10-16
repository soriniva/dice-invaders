#pragma once

#include "Alien.h"

class AlienPack
{
public:
	AlienPack(std::shared_ptr<Engine> engine, 
		int numRow, int numCol);

	void update(float dt);
	void draw();
	void checkCollision(std::shared_ptr<Entity> entity);
	void reset();

	bool isOutsideScreen() const { return m_isOutsideScreen; }
	bool isDestroyed() const { return m_isDestroyed; }

private:
	void packXDirectionChanged(float dir);

private:
	bool m_isOutsideScreen = false;
	bool m_isDestroyed = false;
	int m_numRow = 0;
	int m_numCol = 0;
	bool m_directionChanged = false;
	float m_xDirection = 0.f;
	std::vector<std::shared_ptr<Alien>> m_aliens;
};