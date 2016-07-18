#include<cmath>
#include<windows.h>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"myclock.h"
#include"myshader.h"

#define eps 1e-9
#define PI 3.1415926535



int Clock::ClockDisplay(GLFWwindow* window)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\vertexShader.shader";
	const Char* hour_vertexPath = "E:\\openglDemo\\digitClock\\hour_vertexShader.shader";
	const Char* minuter_vertexPath = "E:\\openglDemo\\digitClock\\minuter_vertexShader.shader";
	const Char* second_vertexPath = "E:\\openglDemo\\digitClock\\second_vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);
	Shader hourShader(hour_vertexPath, fragmentPath);
	Shader minuterShader(minuter_vertexPath, fragmentPath);
	Shader secondShader(second_vertexPath, fragmentPath);


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
	
	// 设置三个时针的数据
	Uint hour_VAO, hour_VBO;
	Uint minute_VAO, minute_VBO;
	Uint second_VAO, second_VBO;

	SetHour(window, hour_VAO, hour_VBO);
	SetMinuter(window, minute_VAO,minute_VBO);
	SetSecond(window, second_VAO, second_VBO);

	while (!glfwWindowShouldClose(window))
	{

		myGetCurrentTime();

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
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

		// 画时钟
		hourShader.Use();
		glm::mat4 trans_hour;
		trans_hour = glm::rotate(trans_hour, -(GLfloat)glm::radians(hourAngle), glm::vec3(0.0f,0.0f,1.0f));
		Uint trans_hour_Loc = glGetUniformLocation(hourShader.Program, "trans_hour");
		glUniformMatrix4fv(trans_hour_Loc, 1, GL_FALSE, glm::value_ptr(trans_hour));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(hour_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// 画分钟
		minuterShader.Use();
		glm::mat4 trans_minuter;
		trans_minuter = glm::rotate(trans_minuter, -(GLfloat)glm::radians(minuterAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		Uint trans_minuter_Loc = glGetUniformLocation(minuterShader.Program, "trans_minuter");
		glUniformMatrix4fv(trans_minuter_Loc, 1, GL_FALSE, glm::value_ptr(trans_minuter));

		glBindVertexArray(minute_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// 画秒针
		secondShader.Use();
		glm::mat4 trans_second;
		trans_second = glm::rotate(trans_second, -(GLfloat)glm::radians(secondAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		Uint trans_second_Loc = glGetUniformLocation(secondShader.Program, "trans_second");
		glUniformMatrix4fv(trans_second_Loc, 1, GL_FALSE, glm::value_ptr(trans_second));

		glBindVertexArray(second_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


int Clock::SetHour(GLFWwindow* window, Uint &hour_VAO, Uint &hour_VBO)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\hour_vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);

	float hour_vertices[] = {
		-0.03f, 0.02f,0.0f,
		-0.03f,-0.02f,0.0f,
		 0.28f, 0.00f,0.0f
	};

	glGenVertexArrays(1, &hour_VAO);
	glGenBuffers(1, &hour_VBO);

	glBindVertexArray(hour_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, hour_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hour_vertices), hour_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	
	return 0;
}

int Clock::SetMinuter(GLFWwindow* window, Uint &minuter_VAO, Uint &minuter_VBO)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\minuter_vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);

	float minuter_vertices[] = {
		-0.02f,-0.04f,0.0f,
		 0.02f,-0.04f,0.0f,
		 0.00f, 0.35f,0.0f
	};

	glGenVertexArrays(1, &minuter_VAO);
	glGenBuffers(1, &minuter_VBO);
	
	glBindVertexArray(minuter_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, minuter_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(minuter_vertices), minuter_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return 0;
}

int Clock::SetSecond(GLFWwindow* window, Uint &second_VAO, Uint &second_VBO)
{
	const Char* vertexPath = "E:\\openglDemo\\digitClock\\second_vertexShader.shader";
	const Char* fragmentPath = "E:\\openglDemo\\digitClock\\fragmentShader.shader";

	Shader ourShader(vertexPath, fragmentPath);

	float second_vertices[] = {
		-0.04f,-0.04f,0.0f,
		-0.01f,-0.04f,0.0f,
		 0.00f, 0.40f,0.0f
	};

	glGenVertexArrays(1, &second_VAO);
	glGenBuffers(1, &second_VBO);

	glBindVertexArray(second_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, second_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_vertices),second_vertices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	return 0;
}

int Clock::myGetCurrentTime()
{
	SYSTEMTIME curtime;
	GetLocalTime(&curtime); // 获取当前时间

	curHour = curtime.wHour;
	curMinuter = curtime.wMinute;
	curSecond = curtime.wSecond;

	if (curHour > 12) curHour -= 12;
	secondAngle = curSecond * 6.0f;
	minuterAngle = curMinuter * 6.0f + curSecond * 0.1f;
	hourAngle = curHour * 30.0f + curMinuter * 0.5f;

	return 1;
}

void Clock::Run(GLFWwindow* window, float hAngle,float mAngle,float sAngle)
{
	ClockDisplay(window);
}
