#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	Shader(std::string vertex_shader, std::string fragment_shader);
	Shader();
	static Shader Parse(const char* filepath);
	~Shader();
	void Use();
	unsigned int GetShaderID();
private:
	unsigned int m_shaderID;
};

enum SHADER_TYPE
{
	DEFAULT = 0,
	VERTEX_SHADER = 1,
	FRAGMENT_SHADER = 2,
};

