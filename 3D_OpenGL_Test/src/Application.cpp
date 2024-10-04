#include "PackageManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods);
void modify_player_position(int x, int y);
void update();
void render();
// GLFW error callback
void glfwErrorCallback(int error, const char* description) {
    std::cout << "GLFW Error (" << error << "): " << description << std::endl;
}

// OpenGL debug output callback (requires OpenGL 4.3+)
void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Debug Output: " << message << std::endl;
}
int playerDirX;
int playerDirY;

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(glfwErrorCallback);
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "TEST", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, glfw_on_key_pressed_callback);

    //float vertices[] =
    //{
    //    -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
    //    0.5f, -0.5f, 1.0f, 0.0f, // bottom right
    //    0.5f, 0.5f, 1.0f, 1.0f, // top right
    //    -0.5f, 0.5f, 0.0f, 1.0f // top left
    //};

    float vertices[] =
    { //     COORDINATES     /  TEXTURE COORDS
        -0.5f, 0.0f,  0.5f,     0.0f, 1.0f,
        -0.5f, 0.0f, -0.5f,    1.0f, 0.0f,
         0.5f, 0.0f, -0.5f,    0.0f, 1.0f,
         0.5f, 0.0f,  0.5f,    1.0f, 1.0f,
         0.0f, 0.8f,  0.0f,    1.0f, 1.0f
    };

    unsigned int indices[]
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    /*unsigned int indices[]
    {
        0,1,2,
        2,3,0
    };*/


    Shader shader = Shader::Parse("res/Basic.txt");
    const char* filepath = "res/grb.png";
    const char* filepath1 = "res/boran.png";

    const GLuint SHADER_PROGRAM = shader.GetShaderID();

    VertexArrayObject vao = VertexArrayObject(SHADER_PROGRAM);
    vao.Bind();
    vao.BufferData(vao.m_arrayBufferID,GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vao.VertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    vao.BufferData(vao.m_elementArrayID,GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vao.VertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(3 * sizeof(float)));

    /* EXPERIMENT! */ vao.SetPos(Vector(1,0,0));

    vao.TextureData(filepath);

    VertexArrayObject vao1 = VertexArrayObject(SHADER_PROGRAM);
    vao1.Bind();
    vao1.BufferData(vao1.m_arrayBufferID, GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vao1.VertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    vao1.BufferData(vao1.m_elementArrayID, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vao1.VertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(3 * sizeof(float)));

    vao1.TextureData(filepath1);



    int uniform = glGetUniformLocation(shader.GetShaderID(), "u_Texture");
    glUniform1i(uniform, 0);

  /*  glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);*/

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    //glEnable(GL_DEPTH_TEST);
    /*std::cout << "INIT TEST " << glGetError() << "\n";*/

    // 1282 - error code 


    /* ╔───────────────────────────────────────────╗ */
    /* │                                           │ */
    /* │  _   _  ____   ____     _   _____  _____  │ */
    /* │ | | | ||  _ \ |  _ \   / \ |_   _|| ____| │ */
    /* │ | | | || |_) || | | | / _ \  | |  |  _|   │ */
    /* │ | |_| ||  __/ | |_| |/ ___ \ | |  | |___  │ */
    /* │  \___/ |_|    |____//_/   \_\|_|  |_____| │ */
    /* │                                           │ */
    /* ╚───────────────────────────────────────────╝ */

    const float PLAYER_SPEED = 2.0;
    float playerPosX = 0.0f;
    float playerPosY = 0.0f;

    glEnable(GL_DEPTH_TEST);

    double oldStartTime = 0;

    const int TICK_RATE = 100;
    int tick_counter = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        double currentTime = glfwGetTime();
        if (currentTime - prevTime >= 1 / 60)
        {
            rotation += 0.5f;
            prevTime = currentTime;
        }
        double deltaTime = currentTime - oldStartTime;
        oldStartTime = currentTime;

        playerPosX = playerDirX * PLAYER_SPEED * deltaTime;
        playerPosY = playerDirY * PLAYER_SPEED * deltaTime;
        vao.AddPos(playerPosX, playerPosY);
        //vao.SetPos(Vector(playerPosX, playerPosY, 0));
        vao.ResetMatrices();

       
        vao.TranslateModel(glm::vec3(vao.m_position.xPos, vao.m_position.yPos, vao.m_position.zPos));
        vao.RotateModel(glm::vec3(0.0f, 1.0f, 0.0), 45.0f);
        vao.ParseMatrices();

        vao.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        vao.Unbind();


        vao1.Bind();
        vao1.ResetMatrices();
        
        vao1.AddPos(playerPosX, playerPosY);
        vao1.TranslateModel(glm::vec3(vao.m_position.xPos - vao1.m_position.xPos, vao1.m_position.yPos - vao.m_position.yPos, 0));
        //vao1.SetPos(Vector(playerPosX, playerPosY, 0));
        vao1.RotateModel(glm::vec3(1.0f, 1.0f, 0.0f), rotation);

        vao1.ParseMatrices(); 

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        vao1.Unbind();



        glfwSwapBuffers(window);

        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
    
}

void update()
{

}

void render()
{

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void modify_player_position(int x, int y)
{
    playerDirX = x;
    playerDirY = y;
}

void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action != GLFW_PRESS)
    {
        return;
    }
    if (key == GLFW_KEY_W)
    {
        modify_player_position(0, 1);
    }
    else if (key == GLFW_KEY_S)
    {
        modify_player_position(0, -1);
    }else if (key == GLFW_KEY_D)
    {
        modify_player_position(1, 0);
    }else if (key == GLFW_KEY_A)
    {
        modify_player_position(-1, 0);
    }
    
    if (key == GLFW_KEY_TAB)
    {
        modify_player_position(0, 0);
    }
    
}
