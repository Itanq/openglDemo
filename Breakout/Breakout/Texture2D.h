#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

class Texture2D
{
public:
	GLuint ID;
	GLuint width, height;
	GLuint Internal_Format;
	GLuint Image_Format;
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Mag;

	Texture2D();
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;
};
