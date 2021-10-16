#pragma once

#include "Engine.h"

static const float MIN_DT = 0.05f;

static const int ROCKET_SPEED = 1000;
static const float ROCKET_COOLDOWN_SEC = 0.5f;
static const int ROCKET_WIDTH = 6;
static const int ROCKET_HEIGHT = 16;
static const int ROCKET_BB_X_OFFSET = 13;
static const int ROCKET_BB_Y_OFFSET = 8;

static const int PLAYER_SPEED = 200;
static const char PLAYER_INITIAL_HEALTH = 3;
static const int PLAYER_BB_X_OFFSET = 2;
static const int PLAYER_BB_Y_OFFSET = 8;
static const int PLAYER_WIDTH = 28;
static const int PLAYER_HEIGHT = 16;
static const int PLAYER_SCORE_POS_X = Engine::CanvasWidth - 100;
static const int PLAYER_SCORE_POS_Y = Engine::FontRowHeight + 5;

static const int BOMB_SPEED = 200;
static const float MIN_BOMB_COOLDOWN_SEC = 3.f;
static const int BOMB_COOLDOWN_BUFFER = 700;
static const int BOMB_WIDTH = 12;
static const int BOMB_HEIGHT = 20;
static const int BOMB_BB_X_OFFSET = 9;
static const int BOMB_BB_Y_OFFSET = 6;

static const int ALIEN_SPEED = 80;
static const int ALIEN_STEP_DOWN_SIZE = Engine::SpriteSize / 2;
static const int ALIEN_WIDTH = 24;
static const int ALIEN_HEIGHT = 24;
static const int ALIEN_ROW_COUNT = 3;
static const int ALIEN_COL_COUNT = 5;
static const char ALIEN_INITIAL_HEALTH = 1;
static const int ALIEN_BB_X_OFFSET = 4;
static const int ALIEN_BB_Y_OFFSET = 4;

static const float SCREEN_X_LIMIT_LEFT = 0.f;
static const float SCREEN_X_LIMIT_RIGHT = Engine::CanvasWidth - Engine::SpriteSize;
static const float SCREEN_Y_VISIBLE_LIMIT_UP = 0.f - Engine::SpriteSize;
static const float SCREEN_Y_VISIBLE_LIMIT_DOWN = Engine::CanvasHeight;