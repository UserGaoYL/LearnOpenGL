
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//	���ڿ�
unsigned int APP_WIDTH = 800;
//	���ڸ�
unsigned int APP_HEIGHT = 480;

//	����û������¼�
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//	�������ڱ仯
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}