
/*
	粒子系统 - 粒子生成器的类
*/

#pragma once

#include<vector>
#include<GL/glew.h>
#include<glm/glm.hpp>

#include "shader.h"
#include"texture2D.h"
#include"gameobject.h"


struct Particle
{
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;
	Particle():Position(0.0f),Velocity(0.0f),Color(1.0f),Life(0.0f){}
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
	void Update(GLfloat dt, GameObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Draw();
private:
	std::vector<Particle> particles;
	GLuint amount;
	Shader shader;
	Texture2D texture;
	GLuint VAO;
	void init();
	GLuint firstUnusedParticle();
	void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};


