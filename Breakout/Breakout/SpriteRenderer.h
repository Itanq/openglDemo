#pragma once

#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"Shader.h"
#include"Texture2D.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.06, glm::vec3 color=glm::vec3(1.0f));
private:
	Shader shader;
	GLuint quadVAO;
	void initRenderData();
};

