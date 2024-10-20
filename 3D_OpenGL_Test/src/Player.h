#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Cell.h"
class Player
{
private:
	unsigned int m_shaderID = -1;
	int m_currentCellSize = 0;
public:
	Player();
	~Player();
	void init(unsigned int shaderID);

	int getCurrentCellSize();
public:
	std::vector<Cell*> cells;
};
