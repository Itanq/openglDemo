#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"shader.h"
#include"camera.h"

#define PI 3.14159267


static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


class Star
{
public:
	Star(){}
	Star(Shader& sphereShader, Shader& trackShader,GLfloat radius);
	~Star();
	void init(GLuint& vao);
	void setStar(glm::vec3 size, GLfloat selfSpeed, GLfloat speed, GLboolean sun = true);
	void drawStar(GLint sphereCount);
private:
	Shader sphereShader,trackShader;
	GLuint sphereVAO, trackVAO, trackCount;
	GLfloat radius,selfSpeed,speed;
	glm::vec3 size;
	glm::mat4 model, view, projection;
	GLfloat trackData[2048];
	int GenerateCircle();
};
