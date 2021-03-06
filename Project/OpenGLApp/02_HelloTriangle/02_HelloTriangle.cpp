
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"


static void OnStart(GLFWwindow* window);
static void OnEnd(GLFWwindow* window);
static void OnUpdate(GLFWwindow* window);

const bool useB = true;


//	两个三角形
float verticesB[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	// second triangle
	 0.0f, -0.5f, 0.0f,  // left
	 0.9f, -0.5f, 0.0f,  // right
	 0.45f, 0.5f, 0.0f   // top 
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

static unsigned int VAO, VBO, EBO, shaderProgram;

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


unsigned int MethodA(const void* data)
{
	//unsigned int VBO, VAO, EBO;
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

	//	声明顶点缓冲对象(Vertex Buffer Objects)
	//unsigned int VBO;
	//	调用函数生成缓冲对象
	glGenBuffers(1,&VBO);

	//	OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
	//	调用glBindBuff把新创建的缓冲绑定到GL_ARRAY_BUFFER上
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	//	glBufferData把用户定义的数据复制到当前绑定缓冲
	//	第一个参数是目标缓冲类型
	//	第二个参数指定传输数据的大小（以字节为单位）
	//	第三个参数是要发送的的实际数据
	//	第四个参数指定我们希望显卡如何管理给定的数据
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticesB), verticesB, GL_STATIC_DRAW);

	//	到此，已经把顶点数据存储到显卡的内存中，用VBO这个顶点缓冲对象管理。


	/*
		顶点数组对象(Vertex Array Object)VAO可以像顶点缓冲对象那样被绑定
		任何随后的顶点属性调用都会存储到这个VAO中，这样的好处是，当配置顶点属性指针时，只需要将那些调用执行一次
		之后再绘制物体的时候只需要绑定相应的VAO就行了。这使在不同顶点数据和属性配置之间切换边得非常简单，
		只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中

		一个顶点数组对象VAO会存储以下内容：
		1.glEnableVertexAttribArray和glDisableVertexAttribArray的调用
		2.通过glVertexAttribPointer设置的顶点属性配置
		3.通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象
	*/

	//	创建并绑定VAO缓冲对象
	//unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//	设置顶点属性指针
	//	glVertexAttribPointer函数告诉OpenGL如何解析顶点数据
	//	第一个参数指定要配置的顶点属性。顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(location)
	//	第二个参数指定顶点属性的大小。顶点属性是一个vec3，由三个值组成，所以是3
	//	第三个参数指定数据类型
	//	第四个参数指定是否希望数据被标准化(Normalize)。GL_TRUE，数据（-1 -> 1）将会被映射到（0 -> 1）
	//	第五个参数指定步长(Stride)，告诉连续顶点属性组之间的间隔，每3个数据一组，所以这里是3*sizeof(float)
	//	第六个参数类型是(void*),表示位置数据在缓冲中起始位置的偏移量(offset)。由于位置数据在数组的开头，所以是0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	return VAO;
}

FuncStruct Run_02_HelloTriangle()
{
	FuncStruct callback;
	callback.win_name = "02_HelloTriangle";
	callback.onStart = OnStart;
	callback.onUpdate = OnUpdate;
	callback.onEnd = OnEnd;
	return callback;
}

void OnStart(GLFWwindow* window)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf(infoLog);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf(infoLog);
	}

	shaderProgram = glCreateProgram();
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

	if (useB)
	{
		VAO = MethodB(NULL);
	}
	else
	{
		VAO = MethodA(NULL);
	}

}

void OnUpdate(GLFWwindow* window)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	if (useB)
	{
		glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesB) / (sizeof(verticesB[0]) * 3));
	}
	else
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void OnEnd(GLFWwindow* window)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

