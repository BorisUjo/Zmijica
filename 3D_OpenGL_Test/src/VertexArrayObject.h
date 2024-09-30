#pragma once
#include "Glfw_Packages.h"
#include <iostream>
class VertexArrayObject
{
public:
	GLuint m_vertexArrayID;
	GLuint m_arrayBufferID;
	GLuint m_elementArrayID;
	GLuint m_textureID;

private:
	int m_textureWidth;
	int m_textureHeight;
	int m_textureComp;

public:
	VertexArrayObject();
	~VertexArrayObject();
	void VertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	void BufferData(GLuint id,GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	void TextureData(const char* filepath);
	void Bind();
	void Unbind();

};