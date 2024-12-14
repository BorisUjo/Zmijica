#pragma once
#include "PackageManager.h"
class SnakeGame
{

private:
	Cell* m_pFood = nullptr;
	Player player;
	Time gameTime;
	unsigned int SHADER_PROGRAM = -1;
private:
	void init();
	void update();
	void render();

	void spawn_food(unsigned int shader);
public:
	SnakeGame();
	~SnakeGame();
	void setPlayerDir();
};