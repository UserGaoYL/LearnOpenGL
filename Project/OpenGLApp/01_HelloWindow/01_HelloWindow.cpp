
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#pragma warning (disable:4819)
//#pragma execution_character_set("utf-8")

const unsigned int Win_Width = 800;
const unsigned int Win_Height = 480;

void processInput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window,int width,int height);

//	main���
int main()
{
	glfwInit();

	//	����OpenGL���汾��(Major)�ʹΰ汾��(Minor)Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	����glfwʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("��ʼ������~");

	//	�������ڶ���
	GLFWwindow* window = glfwCreateWindow(Win_Width, Win_Height,"OpenGLAPP",NULL,NULL);
	if (window == NULL)
	{
		printf("Window ����ʧ��!!!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//	ע�ắ�����������ڱ仯
	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	//	GLAD����������OpenGL����ָ��ģ������ڵ����κ�OpenGL����֮ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD ��ʼ��ʧ��");
		return -1;
	}


	while (!glfwWindowShouldClose(window))
	{
		//	����û�����
		processInput(window);

		//	���������ĻҪʹ�õ���ɫ����glClearʹ��
		//	glClearColor��һ��״̬���ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//	��ջ���λ(Buffer Bit)������ֻ������ɫ������ֻ�����ɫ����
		//	glClear��һ��״̬ʹ�ú���,��ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		//	������ɫ����
		glfwSwapBuffers(window);

		//	�������¼�(���̡�����¼�)�����´���״̬�������ö�Ӧ�Ѿ��������¼�
		glfwPollEvents();
	}

	//	��Ⱦ�������ͷ�֮ǰ�������Դ
	glfwTerminate();

	return 0;
}

//	����û������¼�
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}

//	�������ڱ仯
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}