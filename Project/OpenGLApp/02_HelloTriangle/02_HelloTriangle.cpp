
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

extern unsigned int APP_WIDTH;
extern unsigned int APP_HEIGHT;

extern void processInput(GLFWwindow* window);
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);


float verticesB[] = 
{
	-0.5f, -0.5f, 0.0f, // left  
	0.5f, -0.5f, 0.0f, // right 
	0.0f,  0.5f, 0.0f  // top   
};

float verticesA[] = 
{
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = 
{ 
	// 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

unsigned int MethodA(const void* data);
unsigned int MethodB(const void* data);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



//	入口
int StartHelloTriangle()
{
	glfwInit();

	//	设置OpenGL主版本号(Major)和次版本号(Minor)为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//	告诉glfw使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("初始化窗口~StartHelloTriangle \n");

	//	创建窗口对象
	GLFWwindow* window = glfwCreateWindow(APP_WIDTH, APP_HEIGHT, "OpenGLAPP", NULL, NULL);
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

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		printf(infoLog);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
		printf(infoLog);
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		printf(infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	bool useB = false;
	if (useB)
	{
		VAO = MethodB(NULL);
	}
	else
	{
		VAO = MethodA(NULL);
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


		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		if (useB)
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		//	交换颜色缓冲
		glfwSwapBuffers(window);

		//	检测各种事件(键盘、鼠标事件)、更新窗口状态，并调用对应已经监听的事件
		glfwPollEvents();
	}

	//	渲染结束，释放之前分配的资源
	glfwTerminate();

	return 0;
}

unsigned int MethodA(const void* data)
{
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);

	return VAO;
}

unsigned int MethodB(const void* data)
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO);

	return VAO;
}
