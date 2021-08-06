
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Common/Shader.h>

extern unsigned int APP_WIDTH;
extern unsigned int APP_HEIGHT;

extern void processInput(GLFWwindow* window);
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//	���
int StartShaderWindow()
{
	glfwInit();

	//	����OpenGL���汾��(Major)�ʹΰ汾��(Minor)Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	����glfwʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("��ʼ������ StartShaderWindow ~\n");

	//	�������ڶ���
	GLFWwindow* window = glfwCreateWindow(APP_WIDTH, APP_HEIGHT, "StartShaderWindow", NULL, NULL);
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

	Shader shader("03_HelloShader/03_shader.vert","03_HelloShader/03_shader.frag");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


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


		// render the triangle
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//	������ɫ����
		glfwSwapBuffers(window);

		//	�������¼�(���̡�����¼�)�����´���״̬�������ö�Ӧ�Ѿ��������¼�
		glfwPollEvents();
	}

	//	��Ⱦ�������ͷ�֮ǰ�������Դ
	glfwTerminate();

	return 0;
}