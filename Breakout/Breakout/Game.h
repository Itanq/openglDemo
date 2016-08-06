
#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "gamelevel.h"
#include "powerup.h"

// ��Ϸ��ǰת̬
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// ����
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// ������ײ������ײ��������
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

// ��ʼ����Ҵ�С
const glm::vec2 PLAYER_SIZE(100, 20);

// ��ʼ������ƶ����ٶ�
const GLfloat PLAYER_VELOCITY(500.0f);

// ��ʼ������ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

// ��İ뾶
const GLfloat BALL_RADIUS = 12.5f;

class Game
{
public:
	// ������
    GameState              State;	
    GLboolean              Keys[1024];
    GLboolean              KeysProcessed[1024];
    GLuint                 Width, Height;
    std::vector<GameLevel> Levels;
    std::vector<PowerUp>   PowerUps;
    GLuint                 Level;
    GLuint                 Lives;

	// ������
    Game(GLuint width, GLuint height);
    ~Game();
    // ��ʼ����Ϸ������(shaders/textures/levels)
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    void DoCollisions();
    // ��Ϸ���ú���
    void ResetLevel();
    void ResetPlayer();
    // ľ��
    void SpawnPowerUps(GameObject &block);
    void UpdatePowerUps(GLfloat dt);
};
