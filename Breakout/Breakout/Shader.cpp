/*
	着色器的实现方法
*/

#include<string>
#include<iostream>

#include"Shader.h"

Shader& Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::INFOLOG::\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::INFOLOG::\n" << infoLog << std::endl;
		}
	}
}

void Shader::Compile(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath)
{
	GLuint vertexShader, fragmentShader, geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexPath, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentPath, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	if (geometryPath)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryPath, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, "GEOMETRY");
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	if (geometryPath) glAttachShader(this->ID, geometryShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryPath) glDeleteShader(geometryShader);
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

