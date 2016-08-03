#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include "shader.h"

#define PI 3.1415926
#define NUMBER 406800

class SolarSystem
{
public:
	GLfloat radius;
	GLfloat Radius;
	SolarSystem(GLfloat r = 0.0f, GLfloat R = 0.0f) :radius(r), Radius(R) { puts("defefef"); }
	void Draw(GLFWwindow* window, Shader shader)
	{
		this->Set();
		printf("debugggg");
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();

			glBindVertexArray(VAO);
			glDrawArrays(GL_LINES, 0, index);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}
		glfwTerminate();
	}
private:

	GLuint VAO, VBO;
	GLint index;
	GLfloat vertices[NUMBER];

	void Set()
	{
		this->GenerateData();
		puts("SETSetSETset");
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

	}
	void GenerateData()
	{	
	GLfloat R = 0.45f;
	puts("defefef");
	for (int a = 0; a <= 36; ++a)
	{
		for (int b = 0; b <= 36; ++b)
		{
			GLfloat u = a*(2*PI / 36.0f);
			GLfloat v = b*(2*PI / 36.0f);

			GLfloat x = R*cos(u)*sin(v);
			GLfloat z = R*cos(u)*cos(v);
			GLfloat y = R*sin(u);

			vertices[index++] = x;
			vertices[index++] = y;
			vertices[index++] = z;
		}
	}
	for (int b = 0; b <= 36; ++b)
	{
		for (int a = 0; a <= 36; ++a)
		{
			GLfloat u = a*(2*PI / 36.0f);
			GLfloat v = b*(2*PI / 36.0f);

			GLfloat x = R*cos(u)*sin(v);
			GLfloat z = R*cos(u)*cos(v);
			GLfloat y = R*sin(u);

			vertices[index++] = x;
			vertices[index++] = y;
			vertices[index++] = z;
		}
	}
	}

};