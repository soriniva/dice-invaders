#include "Engine.h"
#include "Entity.h"
#include "Player.h"
#include "AlienPack.h"
#include "Constants.h"

#include <memory>
#include <vector>
#include <string>

bool isGamePaused = false;
std::shared_ptr<Player> player = nullptr;
std::shared_ptr<AlienPack> alienPack = nullptr;


void BuildEnemies(std::shared_ptr<Engine> engine)
{
	alienPack = std::make_shared<AlienPack>(engine, ALIEN_ROW_COUNT, ALIEN_COL_COUNT);
}

void Initialize(std::shared_ptr<Engine> engine)
{
	player = std::make_shared<Player>(engine, PLAYER_SPEED);

	BuildEnemies(engine);
}

void UpdateEntities(float dt)
{
	if (isGamePaused)
	{
		return;
	}

	if (alienPack->isDestroyed())
	{
		alienPack->reset();
	}

	player->update(dt);
	alienPack->update(dt);
}

void RenderEntities()
{
	player->draw();
	alienPack->draw();
}

void CheckCollisions()
{
	if (isGamePaused)
	{
		return;
	}

	alienPack->checkCollision(player);
}

void DrawPlayerInfo(std::shared_ptr<Engine> engine)
{
	std::string playerInfoStr("Score: ");
	playerInfoStr += std::to_string(player->getScore());
	playerInfoStr += "\n";
	playerInfoStr += "Health: ";
	playerInfoStr += std::to_string(player->getHealth());
	engine->drawText(
		playerInfoStr.c_str(),
		PLAYER_SCORE_POS_X,
		PLAYER_SCORE_POS_Y);
}

void CheckGameOver(std::shared_ptr<Engine> engine)
{
	if (!player->isAlive() || alienPack->isOutsideScreen())
	{
		const char message[] = "Game Over!";
		engine->drawText(
			message,
			(Engine::CanvasWidth - (sizeof(message) - 1) * Engine::FontWidth) / 2,
			(Engine::CanvasHeight - Engine::FontRowHeight) / 2);

		isGamePaused = true;
	}
}

void EngineMain()
{
	auto engine = std::make_shared<Engine>();
	Initialize(engine);

	while (engine->startFrame())
	{
		static double oldTimestamp = 0;
		double timestamp = engine->getStopwatchElapsedSeconds();		
		float dt = std::min(static_cast<float>(timestamp - oldTimestamp), MIN_DT);
		oldTimestamp = timestamp;

		UpdateEntities(dt);
		CheckCollisions();
		RenderEntities();

		DrawPlayerInfo(engine);

		CheckGameOver(engine);
	}
}

