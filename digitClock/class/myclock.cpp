#include<cmath>
#include<windows.h>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"myclock.h"
#include"myshader.h"

#define PI 3.1415926535



int Clock::ClockDisplay(GLFWwindow* window)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);

	// 表盘的圆形数据
	float R = 0.45f;	// 表盘的半径大小
	float r = 0.40f;	// 表盘的刻度(內圆半径)大小

	int index = 0,scale_index=0, minuter_index=0;
	float vertices[4024];
	float scale_vertices[4024];
	float minuter_vertices[4024];
	int scale_count = 0, minuter_count = 0;
	Uint scale_indices[100], minuter_indices[1024];
	for (int i = 0; i < 24; ++i) scale_indices[i] = i;
	for (int i = 0; i < 120; ++i) minuter_indices[i] = i;


	for (int angle=0; angle <= 360; ++angle)
	{
		float theta = angle * (PI / 180.0);
		float x = cos(theta)*R;
		float y = sin(theta)*R;
		vertices[index++] = x;
		vertices[index++] = y;
		vertices[index++] = 0.0f;
		// 五分钟刻度
		if (angle % 30 == 0)
		{
			float xx = cos(theta)*r;
			float yy = sin(theta)*r;

			scale_vertices[scale_index++] = x;
			scale_vertices[scale_index++] = y;
			scale_vertices[scale_index++] = 0.0f;
			scale_vertices[scale_index++] = xx;
			scale_vertices[scale_index++] = yy;
			scale_vertices[scale_index++] = 0.0f;

		}
		// 每分钟刻度
		else if (angle % 6 == 0)
		{
			float xx = cos(theta)*0.41;
			float yy = sin(theta)*0.41;
			minuter_vertices[minuter_index++] = x;
			minuter_vertices[minuter_index++] = y;
			minuter_vertices[minuter_index++] = 0.0f;
			minuter_vertices[minuter_index++] = xx;
			minuter_vertices[minuter_index++] = yy;
			minuter_vertices[minuter_index++] = 0.0f;
		}
	}
	int count = 0;
	Uint indices[4048];
	for (int i = 0; i < index; i+=2)
	{
		indices[i] = count++;
		indices[i + 1] = count;
	}
	
	// 表盘的圆
	Uint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	// 五分钟刻度
	Uint scale_VAO, scale_VBO,scale_EBO;
	glGenVertexArrays(1,&scale_VAO);
	glGenBuffers(1, &scale_VBO);
	glGenBuffers(1, &scale_EBO);

	glBindVertexArray(scale_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, scale_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scale_vertices), scale_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scale_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(scale_indices), scale_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	// 每分钟刻度
	Uint minuter_VAO, minuter_VBO, minuter_EBO;
	glGenVertexArrays(1, &minuter_VAO);
	glGenBuffers(1, &minuter_VBO);
	glGenBuffers(1, &minuter_EBO);

	glBindVertexArray(minuter_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, minuter_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(minuter_vertices), minuter_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, minuter_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(minuter_indices), minuter_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glLineWidth(4.5);
		// 画表盘的那个圈
		glBindVertexArray(VAO);
		// count*2-364 一个个试出来的数字............
		glDrawElements(GL_LINES, count*2-364, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 画五分钟的刻度
		glBindVertexArray(scale_VAO);
		glDrawElements(GL_LINES, 26*2, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 画每分钟的刻度
		glLineWidth(1.0);
		glBindVertexArray(minuter_VAO);
		glDrawElements(GL_LINES, 1200 * 2, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

int DrawHour(GLFWwindow* window, float Angle)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);

}

void Clock::Run(GLFWwindow* window, float hAngle,float mAngle,float sAngle)
{
//	ClockDisplay(window);

	SYSTEMTIME curtime;
	GetLocalTime(&curtime); // 获取当前时间

	curHour = curtime.wHour;
	curMinuter = curtime.wMinute;
	curSecond = curtime.wSecond;

	hourAngle = curHour * 360 / 60.0f;
	minuterAngle = curMinuter * 360 / 60.0f;
	hourAngle = (curHour % 12) * 360 / 12.0f + curMinuter * 360 / 12.0 / 60 / 0;


}