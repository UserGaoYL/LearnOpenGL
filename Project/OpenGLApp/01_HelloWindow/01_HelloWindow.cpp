
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"

static void OnStart(GLFWwindow* window);
static void OnEnd(GLFWwindow* window);
static void OnUpdate(GLFWwindow* window);

FuncStruct Run_01_HelloWindow()
{
	FuncStruct callback;
	callback.win_name = "01_HelloWindow";
	callback.onStart = OnStart;
	callback.onUpdate = OnUpdate;
	callback.onEnd = OnEnd;
	return callback;
}

void OnStart(GLFWwindow* window)
{
	printf("OnStart_01\n");
}

void OnUpdate(GLFWwindow* window)
{
}

void OnEnd(GLFWwindow* window)
{
	printf("OnEnd_01\n");
}

