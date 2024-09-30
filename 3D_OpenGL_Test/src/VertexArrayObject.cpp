#include "VertexArrayObject.h"
#include "stb_image.h"
VertexArrayObject::VertexArrayObject()
{
	
	glGenVertexArrays(1, &m_vertexArrayID);

	glGenBuffers(1, &m_arrayBufferID);
	glGenBuffers(1, &m_elementArrayID);
	glGenBuffers(1, &m_textureID);

}

VertexArrayObject::~VertexArrayObject()
{

	// memory fuckup possible below

	glDeleteVertexArrays(1, &m_vertexArrayID); 
	glDeleteBuffers(1, &m_arrayBufferID);
	glDeleteBuffers(1, &m_elementArrayID);
	glDeleteBuffers(1, &m_textureID);
}

void VertexArrayObject::VertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VertexArrayObject::BufferData(GLuint id,GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	std::cout << "Buffer Data called | ID: " << id << "| TARGET:  " << target << std::endl;

	glBindBuffer(target, id);
	glBufferData(target, size, data, usage);
}

void VertexArrayObject::TextureData(const char* filepath)
{
	stbi_set_flip_vertically_on_load(1);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	unsigned char* data = stbi_load(filepath, &m_textureWidth, &m_textureHeight, &m_textureComp, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureWidth, m_textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	if (data)
	{
		stbi_image_free(data);
	}


}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_vertexArrayID);
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementArrayID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);*/

	//glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferID);
	//std::cout << "BIND ERROR CHECK: " << glGetError();


}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0); // below might not be necessary 
	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}
