#pragma once
#include "PackageManager.h"
class SnakeGame
{

private:
	Cell* m_Cells = nullptr;
	Player player;
	Time gameTime;
	unsigned int SHADER_PROGRAM = -1;
private:
	void init();
	void update();
	void render();
public:
	SnakeGame();
	~SnakeGame();
	void setPlayerDir();
};