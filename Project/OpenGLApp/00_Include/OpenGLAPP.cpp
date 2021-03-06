#include <iostream>
#include "Config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern void RunWindow(FuncStruct callback);

extern FuncStruct Run_01_HelloWindow();
extern FuncStruct Run_02_HelloTriangle();
extern FuncStruct Run_03_HelloShader();
extern FuncStruct Run_04_Texture();
extern FuncStruct Run_05_Transform();
extern FuncStruct Run_06_Transform3D();

int main()
{
	RunWindow(Run_06_Transform3D());
	return 0;
}