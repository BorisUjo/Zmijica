#pragma once
#include "Glfw_Packages.h"
#include <iostream>
#include "Vector.h"

/*	VERTEX ARRAY OBJECT:
* 
*  BIND() -> start using this vertex array object in the openGL context
* 
* SetPos(Vector)  --> sets object positions
* ResetMatrices() --> resets the model proj and view matrices
* TranslateModel(vec3) --> translate the object to the specified vec3
* RotateModel(ang,vec) --> rotate the object to the specified angle vec3
* ParseMatrices()     ---> Final step, parses the modified matrices to the shader program
* 
* UNBIND() -> stop using this vertex array object in the openGL context
*/

class VertexArrayObject
{
public:
	GLuint m_vertexArrayID;
	GLuint m_arrayBufferID;
	GLuint m_elementArrayID;
	GLuint m_textureID;
	
	Vector m_position = Vector(0,0);


private:
	int m_textureWidth;
	int m_textureHeight;
	int m_textureComp;

	GLuint m_shaderID;

	glm::mat4 model_matrix;
	glm::mat4 proj_matrix;
	glm::mat4 view_matrix;

	unsigned char* texture_data;


public:
	VertexArrayObject(unsigned int SHADER_PROGRAM);
	~VertexArrayObject();
	void VertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	void BufferData(GLuint id,GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	void TextureData(const char* filepath);
	void SetCameraMatrices();
	void TranslateModel(glm::vec3 translation);
	void RotateModel(glm::vec3 rotation, float angle);
	void ResetMatrices();
	void ParseMatrices();
	void Bind();
	void Unbind();
	GLuint GetShaderID();

	void SetPos(Vector pos);
	void AddPos(Vector pos);
	void AddPos(double x, double y);

};