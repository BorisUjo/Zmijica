#pragma once
#include "Glfw_Packages.h"

class VertexArrayObject
{
public:
	GLuint m_vertexArrayID;
	VertexArrayObject();
	~VertexArrayObject();
	void VertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	void BufferData();
	void Bind();
	void Unbind();

};