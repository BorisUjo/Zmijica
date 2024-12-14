#pragma once
#include "VertexArrayObject.h"
#include <glm/glm.hpp>
#include "glm/ext.hpp"
class Cell
{
private:
	VertexArrayObject m_objectRenderer;
	int gridPosX = 0;
	int gridPosY = 0;
	Color m_colorProperty;

public:
	Cell(unsigned int shader_program);
	Cell(const char* filepath);
	~Cell();
	void Render();
	void Bind();
	void Move(double deltaTime, float xDir, float yDir);
	void SetCellColor(float r, float g, float b);
	void GridMove(int xDir, int yDir);
	void SetPos(int xPos, int yPos);

public:
	bool isFood = false;
	float cellPosX = 0.0f;
	float cellPosY = 0.0f;
	unsigned int indices[6]
	{
		0,1,2,
		2,3,0
	};
	//unsigned int indices[6]  {  // note that we start from 0!
	//	0, 1, 3,  // first Triangle
	//	1, 2, 3   // second Triangle
	//};
};