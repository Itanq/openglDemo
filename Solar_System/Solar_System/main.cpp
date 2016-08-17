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
#include"stars.h"


typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;


Uint WIDTH = 800, HEIGHT = 600;

GLfloat sphereData[8024];

char keys[1024];
GLboolean firstMouse = true;

GLfloat lastX=400,lastY=300;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void Domovement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);

}
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}

}
void mousecallback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}	
void scrollcallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
GLuint loadTexture(const char* path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return textureID;
}
GLFWwindow* myCreateWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SolarSystem", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);
	glfwSetCursorPosCallback(window, mousecallback);
	glfwSetScrollCallback(window, scrollcallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return window;
}
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
int main()
{
	GLFWwindow* window = myCreateWindow();

	const char* sphereVertexPath = "./Shader/vertexShader.glsl";
	const char* sphereFragmentPath = "./Shader/fragmentShader.glsl";

	const char* trackVertexPath = "./Shader/trackVertexShader.glsl";

	Shader sphereShader(sphereVertexPath, sphereFragmentPath);
	Shader trackShader(trackVertexPath, sphereFragmentPath);

	int sphereCount = GenerateSphere(); // 球体
	GLuint sphereVAO, sphereVBO;
	glGenVertexArrays(1, &sphereVAO);
	glGenBuffers(1, &sphereVBO);
	glBindVertexArray(sphereVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphereData), sphereData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Star sun(sphereShader, trackShader, 0.0f);
	sun.init(sphereVAO);
	Star mercury(sphereShader, trackShader, 0.4f);
	mercury.init(sphereVAO);
	Star venus(sphereShader, trackShader, 0.7f);
	venus.init(sphereVAO);
	Star earth(sphereShader, trackShader, 0.95f);
	earth.init(sphereVAO);
	Star moon(sphereShader, trackShader, 0.65f);
	moon.init(sphereVAO);

	Star mars(sphereShader, trackShader, 1.5f);
	mars.init(sphereVAO);
	Star jupiter(sphereShader, trackShader, 1.78f);
	jupiter.init(sphereVAO);
	Star saturn(sphereShader, trackShader, 2.25f);
	saturn.init(sphereVAO);
	Star uranus(sphereShader, trackShader, 2.65f);
	uranus.init(sphereVAO);
	Star neptune(sphereShader, trackShader, 2.45f);
	neptune.init(sphereVAO);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		trackShader.Use();
		sphereShader.Use();

		sun.setStar(glm::vec3(0.7f), 45.0f, 0.0f);
		sun.drawStar(sphereCount);

		mercury.setStar(glm::vec3(0.11f), 45.0f, 8.0f);
		mercury.drawStar(sphereCount);

		venus.setStar(glm::vec3(0.20f), 45.0f, 5.0f);
		venus.drawStar(sphereCount);

		earth.setStar(glm::vec3(0.25f), 45.0f, 1.0f);
		earth.drawStar(sphereCount);

		moon.setStar(glm::vec3(0.10f), 45.0f, 1.0f, GL_FALSE);
		moon.drawStar(sphereCount);

		mars.setStar(glm::vec3(0.15f), 45.0f, 0.90f);
		mars.drawStar(sphereCount);

		jupiter.setStar(glm::vec3(0.35f), 45.0f, 0.78f);
		jupiter.drawStar(sphereCount);


		saturn.setStar(glm::vec3(0.32f), 45.0f, 0.55f);
		saturn.drawStar(sphereCount);

		uranus.setStar(glm::vec3(0.31f), 45.0f, 0.35f);
		uranus.drawStar(sphereCount);

		neptune.setStar(glm::vec3(0.31f), 45.0f, 0.15f);
		neptune.drawStar(sphereCount);

		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

