#pragma once

#ifndef MYCLOCK_H
#define MYCLOCK_H
#include<GL/glew.h>
#include<GLFW/glfw3.h>

class Clock
{
public:
	int secondAngle;
	int minuterAngle;
	int hourAngle;

	int curSecond;
	int curMinuter;
	int curHour;

public:
	Clock(int h = 0, int m = 0, int s = 0) :curHour(h), curMinuter(m), curSecond(s){}
	int ClockDisplay(GLFWwindow* window);
	void Run(GLFWwindow* window,float hAngle,float mAngle,float sAngle);
};

#endif
