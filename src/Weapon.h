#pragma once

#include "Entity.h"

class Weapon : public Entity
{
public:
	enum class Type
	{
		Rocket,
		Bomb,
		Invalid
	};

public:
	Weapon(std::shared_ptr<Engine> engine, Type type, float posX, float posY, int speed);

	void init(float posX, float posY);
	void draw() override;
	void update(float dt) override;
	void handleCollision() override;

private:
	const Type m_type = Type::Invalid;
	Engine::Sprite m_sprite = Engine::Sprite::Bomb;
	float m_boundingBoxXOffset = 0.f;
	float m_boundingBoxYOffset = 0.f;
	float m_yDirection = 1.f;
};