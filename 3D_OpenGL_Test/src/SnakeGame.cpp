#include "SnakeGame.h"
#include "GameConstants.h"
#define TICK_RATE 5
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods);
void handlePlayerInput(const int& key);

Vector snakeDirection = Vector(0, 0);
int currentTickRate = 0;

bool canSpawnCell = false;

SnakeGame::SnakeGame()
{
	GLFWwindow* window;

	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "[GLFW] Failed to initialise glfw";
		return;
	}

	window = glfwCreateWindow(800, 600, "Snake Game", NULL, NULL);
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


	Shader shader = Shader::Parse("res/PlaneShader.txt");
	SHADER_PROGRAM = shader.GetShaderID();

	glUseProgram(SHADER_PROGRAM);
	
	player.cells.push_back(new Cell(SHADER_PROGRAM));

	init();


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

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
}

void SnakeGame::update()
{

	// check if snake direction is valid before entering



	//gameTime.CalculateDeltaTime(glfwGetTime()); 

	if (currentTickRate < TICK_RATE)
	{
		currentTickRate++;
		return;
	}

	// spawn new cell -> move to new func
	if (canSpawnCell)
	{
		Cell* prevLast = player.cells.back();
		player.cells.push_back(new Cell(SHADER_PROGRAM));
		Cell* newLast = player.cells.back();

		std::cout << "Creating new cell, index: " << player.cells.size() << std::endl;
		std::cout << (snakeDirection.xPos * X_STEP) << std::endl;

		newLast->SetPos(prevLast->cellPosX + (snakeDirection.xPos * X_STEP ), prevLast->cellPosY + (snakeDirection.yPos * Y_STEP));

		canSpawnCell = false;

	}


	
	for (int i = player.cells.size() - 1; i > 0; i--)
	{
		player.cells[i]->SetPos(player.cells[i-1]->cellPosX, player.cells[i - 1]->cellPosY);
	}

	player.cells[0]->GridMove(snakeDirection.xPos, snakeDirection.yPos);

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

	else if (key == GLFW_KEY_TAB)
	{
		x = 0;
		y = 0;
	}

	else if (key == GLFW_KEY_R)
	{
		canSpawnCell = true;
		return;
	}

	else
	{
		return;
	}

	snakeDirection.xPos = x;
	snakeDirection.yPos = y;

}
