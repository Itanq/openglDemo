
/*
	后效果实现的库
*/
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture2D.h"
#include "spriterenderer.h"
#include "shader.h"


class PostProcessor
{
public:
    // State
    Shader PostProcessingShader;
    Texture2D Texture;
    GLuint Width, Height;
    // Options
    GLboolean Confuse, Chaos, Shake;
    PostProcessor(Shader shader, GLuint width, GLuint height);
    void BeginRender();
    void EndRender();
    void Render(GLfloat time);
private:
    // Render state
    GLuint MSFBO, FBO;
    GLuint RBO;
    GLuint VAO;
    void initRenderData();
};
