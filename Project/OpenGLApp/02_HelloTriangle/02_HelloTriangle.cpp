
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

extern unsigned int APP_WIDTH;
extern unsigned int APP_HEIGHT;

extern void processInput(GLFWwindow* window);
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//	���
int StartHelloTriangle()
{
	glfwInit();

	//	����OpenGL���汾��(Major)�ʹΰ汾��(Minor)Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	����glfwʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("��ʼ������~StartHelloTriangle \n");

	//	�������ڶ���
	GLFWwindow* window = glfwCreateWindow(APP_WIDTH, APP_HEIGHT, "OpenGLAPP", NULL, NULL);
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
		glClearColor(0.6f, 0.6f, 0.2f, 1.0f);

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