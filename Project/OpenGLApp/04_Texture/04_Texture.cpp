
// 文件名：04_Texture
// 创建时间：2021/8/6 15:49:51

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"
#include <Common/Shader.h>


static Shader shader = Shader(NULL, NULL);
static unsigned int VBO, VAO;

static void OnStart(GLFWwindow* window);
static void OnEnd(GLFWwindow* window);
static void OnUpdate(GLFWwindow* window);

FuncStruct Run_04_Texture()
{
	FuncStruct callback;
	callback.onStart = OnStart;
	callback.onUpdate = OnUpdate;
	callback.onEnd = OnEnd;
	return callback;
}

void OnStart(GLFWwindow* window)
{
}

void OnUpdate(GLFWwindow* window)
{
}

void OnEnd(GLFWwindow* window)
{
}

