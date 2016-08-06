
#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "gamelevel.h"
#include "powerup.h"

// 游戏当前转态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// 方向
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// 用于碰撞检测的碰撞数据类型
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

// 初始化玩家大小
const glm::vec2 PLAYER_SIZE(100, 20);

// 初始化玩家移动的速度
const GLfloat PLAYER_VELOCITY(500.0f);

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

// 球的半径
const GLfloat BALL_RADIUS = 12.5f;

class Game
{
public:
	// 数据区
    GameState              State;	
    GLboolean              Keys[1024];
    GLboolean              KeysProcessed[1024];
    GLuint                 Width, Height;
    std::vector<GameLevel> Levels;
    std::vector<PowerUp>   PowerUps;
    GLuint                 Level;
    GLuint                 Lives;

	// 方法区
    Game(GLuint width, GLuint height);
    ~Game();
    // 初始化游戏的数据(shaders/textures/levels)
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    void DoCollisions();
    // 游戏重置函数
    void ResetLevel();
    void ResetPlayer();
    // 木板
    void SpawnPowerUps(GameObject &block);
    void UpdatePowerUps(GLfloat dt);
};
