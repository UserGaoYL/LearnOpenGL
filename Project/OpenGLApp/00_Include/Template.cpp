
// 文件名：$itemname$
// 创建时间：$time$

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"
#include <Common/Shader.h>
#include <Common/stb_image.h>


static Shader shader = NULL;
static unsigned int VBO, VAO;

static void OnStart(GLFWwindow* window);
static void OnEnd(GLFWwindow* window);
static void OnUpdate(GLFWwindow* window);

extern unsigned int loadTexture(char const* path);


FuncStruct Run_$itemname$()
{
	FuncStruct callback;
	callback.win_name = "$itemname$";
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

