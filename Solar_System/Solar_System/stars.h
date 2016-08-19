#pragma once

#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"Model.h"
#include"Shader.h"
#include"Camera.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

class Star
{
public:
	GLfloat size;
	GLfloat selfSpeed;
	GLfloat radius;
	glm::vec3 position;
	Star(GLfloat size, GLfloat selfSpeed, glm::vec3 position = glm::vec3(0.0f), GLfloat radius = -1.0f) :size(size), selfSpeed(selfSpeed), position(position), radius(radius)
	{
		this->model = glm::mat4();
	}
	~Star() { glDeleteShader(shader.Program); }

	void init(GLchar* path)
	{
		Shader shader("Shader/vertexShader.glsl", "Shader/fragmentShader.glsl");
		Model star(path);

		this->star = star;
		this->shader = shader;

		glDeleteShader(shader.Program);
	}

	void drawStar()
	{
		this->shader.Use();

		setMVP();

		star.Draw(shader);

	}

private:
	Model star;
	Shader shader;
	glm::mat4 model;
	
	void setMVP()
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(camera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f)));

		model = glm::mat4();
		model = glm::translate(model, position);
		if (radius > 0.0f)
		{
			GLfloat x = cos(glfwGetTime())*radius;
			GLfloat z = sin(glfwGetTime())*radius;
			model = glm::rotate(model, (GLfloat)glm::radians(45.f), glm::vec3(1.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(x, 0.0f, z));
			model = glm::rotate(model, -(GLfloat)glm::radians(45.f), glm::vec3(1.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(size));
		model = glm::rotate(model, (GLfloat)glm::radians(54.f), glm::vec3(1.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime()*selfSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	}
};