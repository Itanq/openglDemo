#pragma once

#ifndef MYCLOCK_H
#define MYCLOCK_H
#include<GL/glew.h>
#include<GLFW/glfw3.h>

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
	Clock(int h = 0, int m = 0, int s = 0) :curHour(h), curMinuter(m), curSecond(s){}
	int ClockDisplay(GLFWwindow* window);
	int DrawHour(GLFWwindow* window, float angle);
	int DrawMinuter(GLFWwindow* window, float angle);
	int DrawSecond(GLFWwindow* window, float angle);
	void Run(GLFWwindow* window,float hAngle,float mAngle,float sAngle);
};

#endif
