
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#pragma warning (disable:4819)
//#pragma execution_character_set("utf-8")

const unsigned int Win_Width = 800;
const unsigned int Win_Height = 480;

void processInput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window,int width,int height);

//	main入口
int main()
{
	glfwInit();

	//	设置OpenGL主版本号(Major)和次版本号(Minor)为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	告诉glfw使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("初始化窗口~");

	//	创建窗口对象
	GLFWwindow* window = glfwCreateWindow(Win_Width, Win_Height,"OpenGLAPP",NULL,NULL);
	if (window == NULL)
	{
		printf("Window 创建失败!!!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//	注册函数，监听窗口变化
	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	//	GLAD是用来管理OpenGL函数指针的，所以在调用任何OpenGL函数之前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD 初始化失败");
		return -1;
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
		glClear(GL_COLOR_BUFFER_BIT);

		//	交换颜色缓冲
		glfwSwapBuffers(window);

		//	检测各种事件(键盘、鼠标事件)、更新窗口状态，并调用对应已经监听的事件
		glfwPollEvents();
	}

	//	渲染结束，释放之前分配的资源
	glfwTerminate();

	return 0;
}

//	检测用户输入事件
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}

//	监听窗口变化
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}