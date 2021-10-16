#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "Constants.h"

#include <vector>
#include <functional>

typedef std::function<void(float)> XDirectionChangedFunc;

class Alien : public Entity
{
public:
	Alien(std::shared_ptr<Engine> engine, XDirectionChangedFunc dirChanged, float posX, float posY, int speed);

	void init(float posX, float posY);
	void draw() override;
	void update(float dt) override;
	void checkCollision(std::shared_ptr<Entity> entity) override;
	void handleCollision() override;

	float getXDirection() const { return m_xDirection; }
	void setXDirection(float dir);
	void takeOneStepDown();

	bool isAlive() const { return m_health > 0; }
	bool isOutsideScreen() const { return m_isOutsideScreen; }

private:
	void fireBomb();
	void resetCooldown();

private:
	bool m_isOutsideScreen = false;
	Engine::Sprite m_sprite = Engine::Sprite::Enemy1;
	char m_health = ALIEN_INITIAL_HEALTH;
	float m_xDirection = 1.f;
	float m_bombCooldownSec = 0.f;
	XDirectionChangedFunc m_directionChangedCallback; // Used to notify that the direction has changed
	std::vector<std::shared_ptr<Weapon>> m_bombs;
};