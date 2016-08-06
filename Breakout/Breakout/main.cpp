
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "spriterenderer.h"
#include "resourcemanager.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

GLFWwindow* myCreateWindow()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();

    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}

int main(int argc, char *argv[])
{
	
	GLFWwindow * window = myCreateWindow();

    // 初始化游戏对象
    Breakout.Init();

    // DeltaTime 变量
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    Breakout.State = GAME_ACTIVE;
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		// 处理输入
        Breakout.ProcessInput(deltaTime);

        // 更新
        Breakout.Update(deltaTime);

        // 渲染
        Breakout.Render();

        glfwSwapBuffers(window);
    }
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
		{
			Breakout.Keys[key] = GL_FALSE;
			Breakout.KeysProcessed[key]=GL_FALSE;
		}
    }
}