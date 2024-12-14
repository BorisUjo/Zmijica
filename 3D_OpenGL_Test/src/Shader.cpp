#include "Shader.h"
#include <iostream>
#include <sstream>
#include <fstream>



Shader::Shader(const char* vertex_shader, const char* fragment_shader)
{

    m_shaderID = glCreateProgram();

    unsigned int vertID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertID, 1, &vertex_shader, nullptr);
    glCompileShader(vertID);
    glShaderSource(fragID, 1, &fragment_shader, nullptr);
    glCompileShader(fragID);
    
    glAttachShader(m_shaderID, vertID);
    glAttachShader(m_shaderID, fragID);

    glLinkProgram(m_shaderID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

}

Shader::Shader(std::string vertex_shader, std::string fragment_shader)
{
    m_shaderID = glCreateProgram();

    const char* vert = vertex_shader.c_str();
    const char* frag = fragment_shader.c_str();

    unsigned int vertID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertID, 1, &vert, nullptr);
    glCompileShader(vertID);
    glShaderSource(fragID, 1, &frag, nullptr);
    glCompileShader(fragID);

    glAttachShader(m_shaderID, vertID);
    glAttachShader(m_shaderID, fragID);

    glLinkProgram(m_shaderID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

}
Shader::Shader()
{
    m_shaderID = -1;
    std::cout << "[SHADER] : Generating empty shader class, this will fail... " << std::endl;
}


Shader Shader::Parse(const char* filepath)
{
    std::ifstream stream(filepath);
    std::string line;

    SHADER_TYPE type = SHADER_TYPE::DEFAULT;

    std::stringstream ss[2];
    

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = SHADER_TYPE::VERTEX_SHADER;
                continue;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = SHADER_TYPE::FRAGMENT_SHADER;
                continue;
            }
        }

        ss[(int)type - 1] << line << "\n";
    }

    return Shader(ss[0].str(), ss[1].str());
}

Shader::~Shader()
{
    glDeleteProgram(m_shaderID);
}

void Shader::Use()
{
    glUseProgram(m_shaderID);
}

unsigned int Shader::GetShaderID()
{
    return m_shaderID;
}
