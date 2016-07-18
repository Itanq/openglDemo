#include<cmath>
#include<windows.h>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL.h>
#include"myshader.h"
#include"myclock.h"

#define PI 3.1415926535

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

const Uint WIDTH = 500, HEIGHT = 450;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texture", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);
	glfwSetInputMode(window, GLFW_CURSOR_DISABLED, GL_TRUE);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}

int main()
{

	GLFWwindow* window = InitWindow();

	SYSTEMTIME curtime;
	GetLocalTime(&curtime); // 获取当前时间

	Int curHour = curtime.wHour;
	Int curMinuter = curtime.wMinute;
	Int curSecond = curtime.wSecond;

	if (curHour > 12) curHour -= 12;
	Float secondAngle = curSecond * 6.0f;
	Float minuterAngle = curMinuter * 6.0f + curSecond * 0.1f;
	Float hourAngle = curHour * 30.0f + curMinuter * 0.5f;

	//printf("%.3lf,%.3lf,%.3lf\n", hourAngle, minuterAngle, secondAngle);
	Clock clock(hourAngle,minuterAngle,secondAngle);

	clock.Run(window,0.0,0.0,0.0);

	return 0;
}
