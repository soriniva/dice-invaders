#include "AlienPack.h"
#include "Constants.h"
#include "Utils.h"

#include <functional>

using namespace std::placeholders;

AlienPack::AlienPack(std::shared_ptr<Engine> engine, 
	int numRow, int numCol)
	: m_numRow(numRow)
	, m_numCol(numCol)
{
	auto dirChangeFunc = std::bind(&AlienPack::packXDirectionChanged, this, _1);
	for (int i = 0; i < m_numRow; ++i)
	{
		for (int j = 0; j < m_numCol; ++j)
		{

			auto alien = std::make_shared<Alien>(engine,
				dirChangeFunc,
				static_cast<float>(j * Engine::SpriteSize),
				static_cast<float>(i * Engine::SpriteSize),
				ALIEN_SPEED);
			m_aliens.push_back(alien);
		}
	}
}

void AlienPack::update(float dt)
{
	m_isDestroyed = true;
	for (auto alien : m_aliens)
	{
		alien->update(dt);
		if (alien->isOutsideScreen())
		{
			m_isOutsideScreen = true;
		}
		if (alien->isAlive())
		{
			m_isDestroyed = false;
		}
	}

	if (m_directionChanged)
	{
		for (auto alien : m_aliens)
		{
			alien->setXDirection(m_xDirection);
			alien->takeOneStepDown();
		}
	}
	m_directionChanged = false;
}

void AlienPack::draw()
{
	for (auto alien : m_aliens)
	{
		alien->draw();
	}
}

void AlienPack::checkCollision(std::shared_ptr<Entity> player)
{
	for (auto alien : m_aliens)
	{
		player->checkCollision(alien);
		alien->checkCollision(player);
	}
}

void AlienPack::reset()
{
	for (int i = 0; i < m_numRow; ++i)
	{
		for (int j = 0; j < m_numCol; ++j)
		{
			m_aliens[i * m_numCol + j]->init(static_cast<float>(j * Engine::SpriteSize), 
				static_cast<float>(i * Engine::SpriteSize));
		}
	}
	m_isOutsideScreen = false;
	m_isDestroyed = false;
	m_directionChanged = false;
	m_xDirection = 0.f;
}

void AlienPack::packXDirectionChanged(float dir)
{
	m_directionChanged = true;
	m_xDirection = dir;
}