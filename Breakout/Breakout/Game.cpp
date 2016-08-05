/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resourcemanager.h"
#include "spriterenderer.h"
#include "gameobject.h"
#include"ballobject.h"

// Game-related State data
SpriteRenderer  *Renderer;
GameObject      *Player;
BallObject      *Ball;

Game::Game(GLuint width, GLuint height) 
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height) 
{ 

}

Game::~Game()
{
    delete Renderer;
    delete Player;
	delete Ball;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("Shader/spriteVertexShader.glsl", "Shader/spriteFragmentShader.glsl", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load Texture
    ResourceManager::LoadTexture("Texture/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("Texture/background.jpg", GL_TRUE, "background");
    ResourceManager::LoadTexture("Texture/block.png", GL_TRUE, "block");
    ResourceManager::LoadTexture("Texture/block_solid.png", GL_TRUE, "block_solid");
    ResourceManager::LoadTexture("Texture/paddle.png", GL_TRUE, "paddle");

    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load GameLevel
    GameLevel one; one.Load("GameLevel/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two; two.Load("GameLevel/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three; three.Load("GameLevel/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four; four.Load("GameLevel/four.lvl", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // Configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // Draw background
		//Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200,200), glm::vec2(300,400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(10, 10), glm::vec2(this->Width, this->Height), 0.0f);
        // Draw level
        this->Levels[this->Level].Draw(*Renderer);
        // Draw player
        Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
    }
}


void Game::Update(GLfloat dt)
{
	Ball->Move(dt, this->Width);
	this->DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT])
        {
            if (Player->Position.x >= 0)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
		if (this->Keys[GLFW_KEY_SPACE])
			Ball->Stuck = false;
    }
}

// AABB-AABB Åö×²¼ì²âËã·¨
GLboolean ChekCollision(GameObject &one, GameObject &two)
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	return collisionX && collisionY;
}

// AABB-Cirlc Åö×²¼ì²âËã·¨
GLboolean CheckCollisions(BallObject &one, GameObject two)
{
	glm::vec2 center(one.Position + one.Radius);
	glm::vec2 aabb_half_extens(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extens.x,
		two.Position.y + aabb_half_extens.y
	);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extens, aabb_half_extens);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	return glm::length(difference) < one.Radius;
}
void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			if (ChekCollision(*Ball, box))
				if(!box.IsSolid)
					box.Destroyed = GL_TRUE;
		}
	}
}