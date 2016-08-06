/*
	纹理类的实现方法
*/

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL.h>
#include"Texture2D.h"

Texture2D::Texture2D():width(0),height(0),Internal_Format(GL_RGB),Wrap_S(GL_REPEAT),Wrap_T(GL_REPEAT),Filter_Min(GL_LINEAR),Filter_Mag(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Mag);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
