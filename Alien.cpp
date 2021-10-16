#include "Alien.h"
#include "Utils.h"
#include "Constants.h"
#include "Player.h"

#include <algorithm>
#include <cassert>
#include <time.h>

Alien::Alien(std::shared_ptr<Engine> engine, XDirectionChangedFunc dirChanged, float posX, float posY, int speed)
	: Entity(engine)
	, m_directionChangedCallback(dirChanged)
{
	init(posX, posY);
	m_speed = speed;
	m_boundingBox = {m_posX, m_posY, ALIEN_WIDTH, ALIEN_HEIGHT};
}

void Alien::init(float posX, float posY)
{
	m_sprite = (std::rand() % 2) ? Engine::Sprite::Enemy1 : Engine::Sprite::Enemy2;
	m_posX = posX;
	m_posY = posY;
	m_isVisible = true;
	m_isOutsideScreen = false;
	m_health = ALIEN_INITIAL_HEALTH;
	resetCooldown();
}

void Alien::draw()
{
	for (auto& bomb : m_bombs)
	{
		bomb->draw();
	}

	if (!m_isVisible)
	{
		return;
	}

	m_engine->drawSprite(
		m_sprite,
		(int)m_posX, (int)m_posY);
}

void Alien::update(float dt)
{
	for (auto& bomb : m_bombs)
	{
		bomb->update(dt);
	}

	if (!m_isVisible)
	{
		return;
	}

	// Change position
	m_posX += static_cast<float>(m_speed) * m_xDirection * dt;
	m_posX = std::min(m_posX, SCREEN_X_LIMIT_RIGHT);
	m_posX = std::max(m_posX, SCREEN_X_LIMIT_LEFT);

	// Check screen limits and reverse direction when limits are hit
	if (m_posX >= SCREEN_X_LIMIT_RIGHT || m_posX <= SCREEN_X_LIMIT_LEFT)
	{
		m_xDirection *= -1.f;
		m_directionChangedCallback(m_xDirection);
	}

	updateBoundingBoxPos(ALIEN_BB_X_OFFSET, ALIEN_BB_Y_OFFSET);

	m_bombCooldownSec -= dt;
	fireBomb();

	if (Utils::isCompletelyOutsideScreen(getBoundingBox()))
	{
		m_isVisible = false;
		m_isOutsideScreen = true;
	}
}

void Alien::checkCollision(std::shared_ptr<Entity> entity)
{
	// We only accept collision with Player
	assert(std::dynamic_pointer_cast<Player>(entity) != nullptr);

	if (!entity->isVisible())
	{
		return;
	}

	// First check collision between player ship and alien ship
	if (m_isVisible && Utils::hasCollision(entity->getBoundingBox(), getBoundingBox()))
	{
		entity->handleCollision();
		handleCollision();
	}

	// Then check collision between player and bombs
	for (auto bomb : m_bombs)
	{
		if (bomb->isVisible() && Utils::hasCollision(bomb->getBoundingBox(), entity->getBoundingBox()))
		{
			bomb->handleCollision();
			entity->handleCollision();
		}
	}
}

void Alien::handleCollision()
{
	m_health--;
	m_isVisible = false;
}

void Alien::setXDirection(float dir)
{
	m_xDirection = dir;
}

void Alien::takeOneStepDown()
{
	m_posY += ALIEN_STEP_DOWN_SIZE;
}

void Alien::fireBomb()
{
	if (m_bombCooldownSec <= 0.f)
	{
		auto invsibleRocket = std::find_if(m_bombs.begin(), m_bombs.end(),
			[](std::shared_ptr<Weapon> rocket) { return !rocket->isVisible(); });
		if (invsibleRocket == m_bombs.end())
		{
			auto rocket = std::make_shared<Weapon>(m_engine, Weapon::Type::Bomb, m_posX, m_posY, BOMB_SPEED);
			m_bombs.push_back(rocket);
		}
		// Reuse the invisible bombs instead of creating new ones
		else
		{
			(*invsibleRocket)->init(m_posX, m_posY);
		}

		resetCooldown();
	}
}

void Alien::resetCooldown()
{
	float random = (rand() % BOMB_COOLDOWN_BUFFER) / 100.f;
	m_bombCooldownSec = MIN_BOMB_COOLDOWN_SEC + random;
}