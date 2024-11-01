#include "SnakeGame.h"
#include "GameConstants.h"
#define TICK_RATE 5
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods);
void handlePlayerInput(const int& key);
bool isLegalMove(int currX, int currY, int changeX, int changeY);
void spawn_cell(Player& player, const unsigned int SHADER_PROGRAM);
Vector snakeDirection = Vector(0, 0);
Vector prevDirection = snakeDirection;
int currentTickRate = 0;

bool canSpawnCell = false;
bool isPaused = false;
SnakeGame::SnakeGame()
{
	GLFWwindow* window;

	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "[GLFW] Failed to initialise glfw";
		return;
	}

	window = glfwCreateWindow(600, 600, "Zmijica", NULL, NULL);
	if (!window)
	{
		std::cout << "[GLFW] Failed to initialise window";
		glfwTerminate();
			
		return;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSetKeyCallback(window, glfw_on_key_pressed_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const char* filepath = "res/PlaneShader.txt";

	Shader shader = Shader::Parse(filepath);
	SHADER_PROGRAM = shader.GetShaderID();

	glUseProgram(SHADER_PROGRAM);
	

	init();


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!isPaused)
		{
			update();
		}

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	for (auto* cell : player.cells)
	{
		delete cell;
	}

	player.cells.clear();


	glfwTerminate();


}
SnakeGame::~SnakeGame()
{
}
void SnakeGame::init()
{
	glEnable(GL_DEPTH_TEST);

	player.cells.push_back(new Cell(SHADER_PROGRAM));
	player.cells.push_back(new Cell(SHADER_PROGRAM));
	player.cells.push_back(new Cell(SHADER_PROGRAM));


	player.cells[0]->SetPos(15, 15);
	player.cells[0]->SetCellColor(1.0, 0.8, 0);

	spawn_food(SHADER_PROGRAM);

}

void SnakeGame::update()
{

	if (snakeDirection.xPos == 0 && snakeDirection.yPos == 0)
	{
		return;
	}

	if (currentTickRate < TICK_RATE)
	{
		currentTickRate++;
		return;
	}
	
	for (int i = player.cells.size() - 1; i > 0; i--)
	{
		player.cells[i]->SetPos(player.cells[i-1]->cellPosX, player.cells[i - 1]->cellPosY);
	}

	if (isLegalMove(prevDirection.xPos, prevDirection.yPos, snakeDirection.xPos, snakeDirection.yPos))
	{
		player.cells[0]->GridMove(snakeDirection.xPos, snakeDirection.yPos);
	}



	for (int i = 1; i < player.cells.size(); i++)
	{
		if (player.cells[0]->cellPosX == player.cells[i]->cellPosX && player.cells[0]->cellPosY == player.cells[i]->cellPosY)
		{

			for (int j = 0; j < (player.cells.size() - i); j++)
			{
				int removeIndex = i + j;
				delete player.cells[removeIndex];
			}

			player.cells.resize(i);
		}
	}
	
	
	if (player.cells[0]->cellPosX == m_pFood->cellPosX && player.cells[0]->cellPosY == m_pFood->cellPosY)
	{
		delete m_pFood;
		spawn_food(SHADER_PROGRAM);
		spawn_cell(player, SHADER_PROGRAM);
	}

	
	currentTickRate = 0;



}

void SnakeGame::render()
{
	for (int i = 0; i < player.cells.size(); i++)
	{
		glUseProgram(SHADER_PROGRAM);

		player.cells[i]->Render();

		glDrawElements(GL_TRIANGLES, sizeof(player.cells[i]->indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	if (m_pFood == nullptr)
	{
		return;
	}

	m_pFood->Render();
	glDrawElements(GL_TRIANGLES, sizeof(m_pFood->indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

}

void SnakeGame::spawn_food(unsigned int shader)
{
	m_pFood = new Cell(shader);

	int randGridPosX = (rand() % GRID_WIDTH);
	int randGridPosY = (rand() % GRID_HEIGHT);

	m_pFood->SetCellColor(1, 0, 0);
	m_pFood->SetPos(randGridPosX, randGridPosY);

}

void SnakeGame::setPlayerDir()
{

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action != GLFW_PRESS)
	{
		return;
	}

	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key == GLFW_KEY_R)
	{
		
	}

	handlePlayerInput(key);
	


}

void handlePlayerInput(const int& key)
{
	int x = 0;
	int y = 0;

	if (key == GLFW_KEY_W)
	{
		y = 1;
	}
	else if (key == GLFW_KEY_S)
	{
		y = -1;
	}

	else if (key == GLFW_KEY_D)
	{
		x = 1;
	}
	else if (key == GLFW_KEY_A)
	{
		x = -1;
	}

	else if (key == GLFW_KEY_Q)
	{
		isPaused = !isPaused;
	}
	else if (key == GLFW_KEY_R)
	{
		canSpawnCell = true;
		return;
	}

	if (isLegalMove(snakeDirection.xPos, snakeDirection.yPos, x, y) == false)
	{
		return;
	}

	prevDirection.xPos = snakeDirection.xPos;
	prevDirection.yPos = snakeDirection.yPos;

	snakeDirection.xPos = x;
	snakeDirection.yPos = y;

}

bool isLegalMove(int currX, int currY, int changeX, int changeY)
{
	if (currX == 0 && currY == 0)
	{
		return true;
	}

	if (currX == -changeX || currY == -changeY)
	{
		return false;
	}

	return true;
}

void spawn_cell(Player& player, const unsigned int SHADER_PROGRAM)
{
	Cell* prevLast = player.cells.back();
	player.cells.push_back(new Cell(SHADER_PROGRAM));
	Cell* newLast = player.cells.back();

	std::cout << "Creating new cell, index: " << player.cells.size() << std::endl;

	newLast->SetPos(prevLast->cellPosX + (snakeDirection.xPos), prevLast->cellPosY + (snakeDirection.yPos));

	canSpawnCell = false;
}