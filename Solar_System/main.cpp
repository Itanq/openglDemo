#include<cmath>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<SOIL.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"

#define PI 3.14159267

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

Uint WIDTH = 800, HEIGHT = 600;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

GLFWwindow* InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BasicLighting", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return window;
}

GLfloat sphereData[8024];
GLfloat circleData[2048];

int GenerateSphere()
{
	int index = 0;
	GLfloat R = 0.45f;
	for (int a = 0; a <= 36; ++a)
	{
		for (int b = 0; b <= 36; ++b)
		{
			GLfloat u = a*(2*PI / 36.0f);
			GLfloat v = b*(2*PI / 36.0f);

			GLfloat x = R*cos(u)*sin(v);
			GLfloat z = R*cos(u)*cos(v);
			GLfloat y = R*sin(u);

			sphereData[index++] = x;
			sphereData[index++] = y;
			sphereData[index++] = z;
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

			sphereData[index++] = x;
			sphereData[index++] = y;
			sphereData[index++] = z;
		}
	}
	return index;
}

int GenerateCircle()
{
	int index = 0;
	GLfloat R = 0.75f;
	for (int i = 0; i <= 360; ++i)
	{
		float u = i*(PI / 180.0f);
		float x = R*cos(u);
		float y = R*sin(u);
		circleData[index++] = x;
		circleData[index++] = y;
		circleData[index++] = 0.0f;
	}
	return index;
}

int main()
{
	GLFWwindow* window = InitWindow();

	const char* sphereVertexPath = "E:\\OpenGL\\OpenGL_test1\\OpenGL_test1\\vertexShader.glsl";
	const char* sphereFragmentPath = "E:\\OpenGL\\OpenGL_test1\\OpenGL_test1\\fragmentShader.glsl";

	const char* circleVertexPath = "E:\\OpenGL\\OpenGL_test1\\OpenGL_test1\\circleVertexShader.glsl";

	Shader sphereShader(sphereVertexPath, sphereFragmentPath);
	Shader circleShader(circleVertexPath, sphereFragmentPath);

	int sphereCount = GenerateSphere(); // 球体数据
	int circleCount = GenerateCircle(); //圆形数据

	GLuint sphereVAO, sphereVBO;
	glGenVertexArrays(1, &sphereVAO);
	glGenBuffers(1, &sphereVBO);

	glBindVertexArray(sphereVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphereData), sphereData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	GLuint circleVAO,circleVBO;
	glGenVertexArrays(1, &circleVAO);
	glGenBuffers(1, &circleVBO);
	glBindVertexArray(circleVAO);

	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circleData), circleData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		circleShader.Use();

		glBindVertexArray(circleVAO);
		glDrawArrays(GL_LINES, 0, circleCount);
		glBindVertexArray(0);

		
		sphereShader.Use();

		glm::mat4 model, view, projection;

		glBindVertexArray(sphereVAO);

		model = glm::mat4();
		view = glm::mat4();
		projection = glm::mat4();

		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime()*45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_LINES, 0, sphereCount);


		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.55f, -0.5f, -0.23f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime()*65.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		view = glm::mat4();
		GLfloat r = 0.75f;
		GLfloat x = (GLfloat)cos(glfwGetTime())*r;
		GLfloat y = (GLfloat)sin(glfwGetTime())*r;
		view = glm::lookAt(glm::vec3(x, y, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		projection = glm::mat4();
		projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(sphereShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_LINES, 0, sphereCount);
		
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

