#include "Cell.h"

extern int GRID_WIDTH;
extern int GRID_HEIGHT;


Cell::Cell(unsigned int shader_program)
{
	std::cout << "[CELL CONSTRUCTOR] : Initialising cell" <<std::endl;
	
	m_objectRenderer.SetShaderID(shader_program);
	m_objectRenderer.Bind();

	//float vertex_data[] =
	//{
	//	-0.05f, -0.05f,
	//	0.05f, -0.05f,
	//	0.05f, 0.05f,
	//	-0.05f, 0.05f
	//};
	float vertex_data[] =
	{
		-0.25f, -0.25f,
		0.25f, -0.25f,
		0.25f, 0.25f,
		-0.25f, 0.25f
	};

	m_objectRenderer.BufferData(m_objectRenderer.m_arrayBufferID, GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	m_objectRenderer.VertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	m_objectRenderer.BufferData(m_objectRenderer.m_elementArrayID, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_objectRenderer.ResetMatrices();

	/*double randR = (rand() % 100) / 100.0;
	double randG = (rand() % 100) / 100.0;
	double randB = (rand() % 100) / 100.0;*/

	
	m_colorProperty = Color(0, 1, 0);

	m_objectRenderer.SetColor(0,1,0);
	//m_objectRenderer.ParseMatrices();
}

Cell::Cell(const char* filepath)
{
	std::cout << "[CELL CONSTRUCTOR] : Initialising cell, generating new shader" << std::endl;

	Shader shader = Shader::Parse(filepath);

	m_objectRenderer.SetShader(shader);
	m_objectRenderer.Bind();

	float vertex_data[] =
	{
		-0.1f, -0.1f,
		0.1f, -0.1f,
		0.1f, 0.1f,
		-0.1f, 0.1f
	};


	m_objectRenderer.BufferData(m_objectRenderer.m_arrayBufferID, GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	m_objectRenderer.VertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	m_objectRenderer.BufferData(m_objectRenderer.m_elementArrayID, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_objectRenderer.ResetMatrices();

	/*double randR = (rand() % 100) / 100.0;
	double randG = (rand() % 100) / 100.0;
	double randB = (rand() % 100) / 100.0;*/

	//m_objectRenderer.SetColor(1.0f, 0.5f, 0.2f);
	m_objectRenderer.SetColor(1.0, 0, 0);
	//m_objectRenderer.ParseMatrices();
}

void Cell::GridMove(int xDir, int yDir)
{
	cellPosX += xDir;
	cellPosY += yDir;

	if (cellPosX > GRID_WIDTH)
	{
		cellPosX = 0;
	}
	if (cellPosX < 0)
	{
		cellPosX = GRID_HEIGHT;
	}

	if (cellPosY > GRID_HEIGHT)
	{
		cellPosY = 0;
	}
	if (cellPosY < 0)
	{
		cellPosY = GRID_HEIGHT;
	}


}
Cell::~Cell()
{
	std::cout << "[CELL] : Destroying cell" << std::endl;
}

void Cell::Bind()
{
	m_objectRenderer.Bind();
}




void Cell::Render()
{

	m_objectRenderer.Bind();

	m_objectRenderer.SetColor(m_colorProperty.R, m_colorProperty.G, m_colorProperty.B);

	m_objectRenderer.ResetMatrices();

	m_objectRenderer.TranslateModel(glm::vec3(cellPosX, cellPosY, 0));

	m_objectRenderer.ParseMatrices();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_objectRenderer.m_elementArrayID); 




}

void Cell::SetPos(int xPos, int yPos)
{
	cellPosX = xPos;
	cellPosY = yPos;
}

void Cell::SetCellColor(float r, float g, float b)
{
	m_colorProperty.R = r;
	m_colorProperty.G = g;
	m_colorProperty.B = b;
}

// a more abstract move function beyond this
void Cell::Move(double deltaTime, float xDir, float yDir)
{
	m_objectRenderer.ResetMatrices();

	// 3.3205

	std::cout << cellPosY << std::endl;

	cellPosX += xDir * deltaTime;
	cellPosY += yDir * deltaTime;
	
	//if (cellPosX > 1.36f || cellPosX < -1.36f)
	//{
	//	//cellPosX = -1.36f;
	//	cellPosX = -cellPosX;
	//}

	//if (cellPosY > 1.83f)
	//{
	//	cellPosY = -0.88f;
	//}
	//else if (cellPosY < -0.88f)
	//{
	//	cellPosY = 1.83f;
	//}


	m_objectRenderer.TranslateModel(glm::vec3(float(cellPosX), float(cellPosY), 0));

	m_objectRenderer.ParseMatrices();

}
