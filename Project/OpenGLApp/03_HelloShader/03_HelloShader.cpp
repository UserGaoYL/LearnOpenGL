
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Common/Shader.h>
#include "Config.h"


static float vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};

static Shader shader = Shader(NULL,NULL);
static unsigned int VBO, VAO;

static void OnStart(GLFWwindow* window);
static void OnEnd(GLFWwindow* window);
static void OnUpdate(GLFWwindow* window);

FuncStruct Run_03_HelloShader()
{
	FuncStruct callback;
	callback.onStart = OnStart;
	callback.onUpdate = OnUpdate;
	callback.onEnd = OnEnd;
	return callback;
}

void OnStart(GLFWwindow* window)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = Shader("03_shader.vert", "03_shader.frag");
}

void OnUpdate(GLFWwindow* window)
{
	shader.use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OnEnd(GLFWwindow* window)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}