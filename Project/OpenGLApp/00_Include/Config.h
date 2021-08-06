#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef void (*CALLBACK)(GLFWwindow * window);

struct FuncStruct
{
	CALLBACK onStart = NULL;
	CALLBACK onUpdate = NULL;
	CALLBACK onEnd = NULL;
};