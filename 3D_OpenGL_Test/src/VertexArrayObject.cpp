#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArrayObject::VertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}
