#include <iostream>
#include "Vertex.h"
#include "RenderObject.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

std::vector<RenderObject> _renderObjects;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Render_figure(RenderObject renderObject, GLint polygonMode)
{

}


int main()
{
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetKeyCallback(window, key_callback);
	
	glViewport(0, 0, width, height);
	_renderObjects.push_back(RenderObject(CreateSolidCube(0.5, 0.0, 2.0, 0.0), new GLint[4]{240 ,128 ,128, 255}, new GLint[4]{ 240 ,128 ,128, 255 }));
	for (int i = 0; i < 10; i++)
	{
		_renderObjects.push_back(RenderObject(CreateSolidCube(0.5f,  1, 2.0f - (float)i, 0.0f), new GLint[4]{ 240 ,128 ,128, 255 }, new GLint[4]{ 240 ,128 ,128, 255 }));
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram();
		for(int i = 0; i < _renderObjects.size(); i++)
		{
			Render_figure(_renderObjects[i], GL_FILL);
			const GLint* color = { _renderObjects[i].color_obj };
			//glUniform4iv(19, 4, color);
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();

	return 0;
}