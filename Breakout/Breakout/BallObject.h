/*
	球对象的类
*/
#pragma once

#include"gameobject.h"

class BallObject :public GameObject
{
public:
	GLfloat Radius;
	GLboolean Stuck;
	GLboolean Sticky, PassThrough;

	BallObject();
	BallObject(glm::vec2 pos, GLfloat raidus, glm::vec2 velocity, Texture2D sprite);
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};
