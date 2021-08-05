
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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