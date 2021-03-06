
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"
#include <Common/stb_image.h>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <Common/Shader.h>

using namespace std;

//	窗口宽
unsigned int APP_WIDTH = 800;
//	窗口高
unsigned int APP_HEIGHT = 480;

//	检测用户输入事件
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//	监听窗口变化
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void RunWindow(FuncStruct callback)
{
	glfwInit();

	//	设置OpenGL主版本号(Major)和次版本号(Minor)为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	告诉glfw使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const char* name = "OpenGLAPP";
	if (callback.win_name != NULL)
	{
		name = callback.win_name;
	}

	//	创建窗口对象
	GLFWwindow* window = glfwCreateWindow(APP_WIDTH, APP_HEIGHT, name, NULL, NULL);
	if (window == NULL)
	{
		printf("Window 创建失败!!!");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	//	注册函数，监听窗口变化
	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	//	GLAD是用来管理OpenGL函数指针的，所以在调用任何OpenGL函数之前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD 初始化失败");
		return;
	}
	if (callback.onStart != NULL)
	{
		callback.onStart(window);
	}

	while (!glfwWindowShouldClose(window))
	{
		//	检测用户输入
		processInput(window);

		//	设置清空屏幕要使用的颜色，供glClear使用
		//	glClearColor是一个状态设置函数
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//	清空缓冲位(Buffer Bit)，这里只考虑颜色，所以只清空颜色缓冲
		//	glClear是一个状态使用函数,它使用了当前的状态来获取应该清除为的颜色
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


		if (callback.onUpdate)
		{
			callback.onUpdate(window);
		}

		//	交换颜色缓冲
		glfwSwapBuffers(window);

		//	检测各种事件(键盘、鼠标事件)、更新窗口状态，并调用对应已经监听的事件
		glfwPollEvents();
	}

	if (callback.onEnd)
	{
		callback.onEnd(window);
	}


	//	渲染结束，释放之前分配的资源
	glfwTerminate();
}

std::wstring ProjectPath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, buffer);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

std::wstring to_wide_string(const std::string& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

std::string to_byte_string(const std::wstring& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(input);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
	stbi_set_flip_vertically_on_load(true); 
	wstring root = ProjectPath();
	string filePath = to_byte_string(root) + "/OpenGLApp/Resources/" + path;
	//printf(filePath.c_str());

	//	创建纹理id
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	//	加载纹理资源
	//	资源路径、宽、高、颜色通道数
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = 0;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		//	绑定纹理
		glBindTexture(GL_TEXTURE_2D, textureID);

		//	信息填充，把纹理图像附加到绑定的纹理对象上
		//	第一个参数，指定纹理目标(Target)
		//	第二个参数，指定纹理多级渐远纹理的级别
		//	第三个参数，告诉OpenGL我们希望把纹理存储为何种格式。
		//	第四五个参数，表示最终纹理的宽高
		//	第六个参数默认为0（历史遗留问题）
		//	第七、八个参数定义了源图的格式和数据类型。这里我们使用RGB值加载图像，并存储为char(byte)数组
		//	最后一个参数是真正的图像数据
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//	设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "\nTexture failed to load at path: " << filePath.c_str() << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}