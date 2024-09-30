#include "PackageManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_on_key_pressed_callback(GLFWwindow* window, int key, int scan, int action, int mods);
void modify_player_position(int x, int y);

int playerDirX;
int playerDirY;

int main(void)
{
    GLFWwindow* window;

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


    Shader shader = Shader::Parse("res/Basic.txt");

    int width, height, comp;
    const char* filepath = "res/grb.png";

    stbi_set_flip_vertically_on_load(1);

    unsigned char* img_data = stbi_load(filepath, &width, &height, &comp, 4);


    // START

    unsigned int vao, array_buffer_id;
    unsigned int ebo;
    unsigned int texture;


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);



    glGenBuffers(1, &array_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // END

    int uniform = glGetUniformLocation(shader.GetShaderID(), "u_Texture");
    glUniform1i(uniform, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    std::cout << "INIT TEST " << glGetError() << "\n";



    if (img_data)
    {
        stbi_image_free(img_data);
    }
    



/*
*_   _  _____ ______   ___   _____  _____
| | | || ___ \|  _  \ / _ \ |_   _||  ___|
| | | || |_/ /| | | |/ /_\ \  | |  | |__  
| | | ||  __/ | | | ||  _  |  | |  |  __| 
| |_| || |    | |/ / | | | |  | |  | |___ 
 \___/ \_|    |___/  \_| |_/  \_/  \____/ 
                                          
*/

    const float PLAYER_SPEED = 2;
    float playerPosX = 0.0f;
    float playerPosY = 0.0f;

    double oldStartTime = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        //std::cout << glGetError() << "\n";
        double currentTime = glfwGetTime();
        if (currentTime - prevTime >= 1 / 60)
        {
            rotation += 0.5f;
            //rotation = 360 * sin(glfwGetTime());
            prevTime = currentTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        double deltaTime = currentTime - oldStartTime;
        oldStartTime = currentTime;

        playerPosX += playerDirX * PLAYER_SPEED * deltaTime;
        playerPosY += playerDirY * PLAYER_SPEED * deltaTime;

        std::cout << playerPosX << "\n";

        model = glm::translate(model, glm::vec3(playerPosX, playerPosY, -5));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.GetShaderID(), "model");
        int viewLoc = glGetUniformLocation(shader.GetShaderID(), "view");
        int projLoc = glGetUniformLocation(shader.GetShaderID(), "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


        glBindVertexArray(vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
    
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
    
}
