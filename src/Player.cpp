#include "Player.h"
#include "Constants.h"
#include "Utils.h"
#include "Alien.h"

#include <algorithm>
#include <iostream>
#include <cassert>

Player::Player(std::shared_ptr<Engine> engine, int speed)
	: Entity(engine)
{
	init();
	m_speed = speed;
	m_boundingBox = Rectangle{ m_posX + PLAYER_BB_X_OFFSET,
		m_posY + PLAYER_BB_Y_OFFSET,
		PLAYER_WIDTH,
		PLAYER_HEIGHT };
}

void Player::init()
{
	m_posX = (Engine::CanvasWidth - Engine::SpriteSize) / 2;
	m_posY = Engine::CanvasHeight - Engine::SpriteSize;
	m_health = PLAYER_INITIAL_HEALTH;
	m_score = 0;
}

void Player::draw()
{
	m_engine->drawSprite(
		Engine::Sprite::Player,
		(int)m_posX, (int)m_posY);

	for (auto rocket : m_rockets)
	{
		rocket->draw();
	}
}

void Player::update(float dt)
{
	m_rocketCooldownSec -= dt;

	Engine::PlayerInput keys = m_engine->getPlayerInput();
	if (keys.left)
	{
		m_posX -= static_cast<float>(m_speed) * dt;
		m_posX = std::max(m_posX, SCREEN_X_LIMIT_LEFT);
	}
	if (keys.right)
	{
		m_posX += static_cast<float>(m_speed) * dt;
		m_posX = std::min(m_posX, SCREEN_X_LIMIT_RIGHT);
	}
	if (keys.fire)
	{
		fireRocket();
	}

	updateBoundingBoxPos(PLAYER_BB_X_OFFSET, PLAYER_BB_Y_OFFSET);

	for (auto& rocket : m_rockets)
	{
		rocket->update(dt);
	}
}

void Player::checkCollision(std::shared_ptr<Entity> entity)
{
	// We only accept collisions with aliens
	assert(std::dynamic_pointer_cast<Alien>(entity) != nullptr);

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

	// Then check the collision between rockets and alien
	for (auto rocket : m_rockets)
	{
		if (rocket->isVisible() && Utils::hasCollision(rocket->getBoundingBox(), entity->getBoundingBox()))
		{
			rocket->handleCollision();
			entity->handleCollision();
			// Rocket has hit an alien, increase the score
			m_score++;
		}
	}
}

void Player::handleCollision()
{
	m_health--;
}

void Player::fireRocket()
{
	if (m_rocketCooldownSec <= 0.f)
	{
		auto invsibleRocket = std::find_if(m_rockets.begin(), m_rockets.end(), 
			[](std::shared_ptr<Weapon> rocket) { return !rocket->isVisible(); });
		if (invsibleRocket == m_rockets.end())
		{
			auto rocket = std::make_shared<Weapon>(m_engine, Weapon::Type::Rocket, m_posX, m_posY, ROCKET_SPEED);
			m_rockets.push_back(rocket);
		}
		// Reuse the invisible rockets instead of creating new ones
		else
		{
 			(*invsibleRocket)->init(m_posX, m_posY);
		}

		m_rocketCooldownSec = ROCKET_COOLDOWN_SEC;
	}
}