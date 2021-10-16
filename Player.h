#pragma once

#include <vector>
#include <queue>

#include "Entity.h"
#include "Weapon.h"
#include "Constants.h"

class Alien;

class Player : public Entity
{
public:
	Player(std::shared_ptr<Engine> engine, int speed);

	void init();
	void draw() override;
	void update(float dt) override;
	void checkCollision(std::shared_ptr<Entity> entity) override;
	void handleCollision() override;

	bool isAlive() const { return m_health > 0; }
	unsigned int getScore() const { return m_score; }
	char getHealth() const { return m_health; }

private:
	void fireRocket();

private:
	char m_health = PLAYER_INITIAL_HEALTH;
	unsigned int m_score = 0;
	float m_rocketCooldownSec = 0.f;
	std::vector<std::shared_ptr<Weapon>> m_rockets;
};