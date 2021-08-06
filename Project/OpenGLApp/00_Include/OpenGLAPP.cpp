#include <iostream>
#include "Config.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>



extern void RunWindow(FuncStruct callback);


extern FuncStruct Run_01_HelloWindow();
extern FuncStruct Run_02_HelloTriangle();
extern FuncStruct Run_03_HelloShader();
extern FuncStruct Run_04_Texture();


int main()
{
	RunWindow(Run_04_Texture());
	return 0;
}

