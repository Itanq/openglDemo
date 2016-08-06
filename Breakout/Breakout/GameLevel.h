
/*
	游戏难度的实现类
*/

#pragma once
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gameobject.h"
#include "spriterenderer.h"
#include "resourcemanager.h"


class GameLevel
{
public:
    // Level state
    std::vector<GameObject> Bricks;
    GameLevel() { }
    void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void      Draw(SpriteRenderer &renderer);
    GLboolean IsCompleted();
private:
    void      init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};
