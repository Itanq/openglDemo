#pragma once

#ifndef MYCLOCK_H
#define MYCLOCK_H
#include<GL/glew.h>
#include<GLFW/glfw3.h>

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

class Clock
{
public:
	float secondAngle;
	float minuterAngle;
	float hourAngle;

	int curSecond;
	int curMinuter;
	int curHour;

public:
	Clock(int h = 0, int m = 0, int s = 0) :curHour(h), curMinuter(m), curSecond(s) { secondAngle = minuterAngle = secondAngle = 0.0; }
	int ClockDisplay(GLFWwindow* window);
	int myGetCurrentTime();
	int SetHour(GLFWwindow* window, Uint &VAO, Uint &VBO);
	int SetMinuter(GLFWwindow* window, Uint &VAO, Uint &VBo);
	int SetSecond(GLFWwindow* window, Uint &VAO, Uint &VBO);
	void Run(GLFWwindow* window,float hAngle,float mAngle,float sAngle);
};


#endif
