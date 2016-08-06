/*
	增加的下掉的木板类
*/
#pragma once
#include<string>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include"gameobject.h"

const glm::vec2 SIZE(60, 20);
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp :public GameObject
{
public:
	std::string Type;
	GLfloat Duration;
	GLboolean Activated;
	PowerUp(std::string type,glm::vec3 color,GLfloat duration,glm::vec2 position,Texture2D texture):GameObject(position,SIZE,texture,color,VELOCITY),Type(type),Duration(duration),Activated(){}
};
