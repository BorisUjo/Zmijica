#include "VertexArrayObject.h"
VertexArrayObject::VertexArrayObject(unsigned int SHADER_PROGRAM)
{
	std::cout << "[VAO CONSTRUCTOR] : Initiliasing VAO" << std::endl;

	m_shaderID = SHADER_PROGRAM;

	glGenVertexArrays(1, &m_vertexArrayID);

	glGenBuffers(1, &m_arrayBufferID);
	glGenBuffers(1, &m_elementArrayID);
	glGenBuffers(1, &m_textureID);

}
VertexArrayObject::VertexArrayObject(Shader& shader)
{
	std::cout << "[VAO CONSTRUCTOR] : Initiliasing VAO, generating new shader" << std::endl;

	m_programShader = shader;
	m_shaderID = m_programShader.GetShaderID();

	glGenVertexArrays(1, &m_vertexArrayID);

	glGenBuffers(1, &m_arrayBufferID);
	glGenBuffers(1, &m_elementArrayID);
	glGenBuffers(1, &m_textureID);
}
VertexArrayObject::VertexArrayObject()
{
	std::cout << "[VAO CONSTRUCTOR] : VAO init...." << std::endl;

	glGenVertexArrays(1, &m_vertexArrayID);

	glGenBuffers(1, &m_arrayBufferID);
	glGenBuffers(1, &m_elementArrayID);
	glGenBuffers(1, &m_textureID);
}
VertexArrayObject::~VertexArrayObject()
{

	std::cout << "[VAO] : Destroying VAO" << std::endl;

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
	//std::cout << "Buffer Data sjeban? | ID: " << id << "| TARGET:  " << target << std::endl;
	
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

void VertexArrayObject::SetCameraMatrices()
{

}

void VertexArrayObject::TranslateModel(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix, translation);
}

void VertexArrayObject::RotateModel(glm::vec3 rotation, float angle)
{
	model_matrix = glm::rotate(model_matrix, glm::radians(angle), rotation);
}

void VertexArrayObject::ResetMatrices()
{
	model_matrix = glm::mat4(1.0f);
	view_matrix = glm::mat4(1.0f);
	proj_matrix = glm::mat4(1.0f);
}

void VertexArrayObject::ParseMatrices()
{
	view_matrix = glm::translate(view_matrix, glm::vec3(0.0, -0.5f, -4.0f));
	//proj_matrix = glm::perspective(glm::radians(45.0f), (800.0f / 600.0f), 0.1f, 100.0f);
	proj_matrix = glm::ortho(0.0f, 30.0f, 0.0f, 30.0f, 0.0f, 25.0f);
	int modelLoc = glGetUniformLocation(m_shaderID, "model");
	int viewLoc = glGetUniformLocation(m_shaderID, "view");
	int projLoc = glGetUniformLocation(m_shaderID, "proj");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj_matrix));

}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0); 
}

void VertexArrayObject::SetColor(float r, float g, float b)
{
	m_objectColor.R = r;
	m_objectColor.G = g;
	m_objectColor.B = b;

	glUniform1f(glGetUniformLocation(m_shaderID, "R"), r);
	glUniform1f(glGetUniformLocation(m_shaderID, "G"), g);
	glUniform1f(glGetUniformLocation(m_shaderID, "B"), b);
	glUniform1f(glGetUniformLocation(m_shaderID, "A"), 1.0f);

}

void VertexArrayObject::SetColor(float r, float g, float b, float alpha)
{
	m_objectColor.R = r;
	m_objectColor.G = g;
	m_objectColor.B = b;
	m_objectColor.A = alpha;
}

void VertexArrayObject::SetShaderID(unsigned int shader_id)
{
	m_shaderID = shader_id;
}

void VertexArrayObject::SetShader(Shader shader)
{
	m_programShader = Shader(shader);
	std::cout << m_programShader.GetShaderID();
	std::cout << 2;
}

void VertexArrayObject::UseShaderProgram()
{
	if (m_programShader.GetShaderID() == -1)
	{
		return;
	}

	std::cout << m_programShader.GetShaderID() << std::endl;

	m_programShader.Use();

}

void VertexArrayObject::SetPos(Vector pos)
{
	this->m_position = pos;
}

void VertexArrayObject::AddPos(Vector pos)
{
	this->m_position.xPos += pos.xPos;
	this->m_position.yPos += pos.yPos;
}

void VertexArrayObject::AddPos(double x, double y)
{
	m_position.xPos += x;
	m_position.yPos += y;
}

GLuint VertexArrayObject::GetShaderID()
{
	return m_shaderID;
}
