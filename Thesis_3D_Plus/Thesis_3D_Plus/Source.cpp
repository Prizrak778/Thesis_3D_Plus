#include <iostream>
#include <string>
#include <fstream>
#include "Vertex.h"
#include "RenderObject.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <glm\vec4.hpp>

std::vector<RenderObject> _renderObjects;
int _program_contour, _program;
glm::vec4 test;

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
	renderObject.Bind();
	//glUniformMatrix4fv(20, false, _view);
	//glUniformMatrix4fv(22, false, _Modelview);
	renderObject.PolygonMode_now(polygonMode);
}

GLuint CompileShaders(std::string VertexString, std::string FragmentString, std::string GeometricString = "")
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string str;
	std::ifstream file(VertexString, std::ios::in);
	if (file.is_open())
	{
		std::copy(
			std::istream_iterator<char>(file),
			std::istream_iterator<char>(),
			std::insert_iterator<std::string>(str, str.begin()));
		const GLchar* textshader = (const GLchar*)str.c_str();
		glShaderSource(vertexShader, 1, &textshader, 0);
		glCompileShader(vertexShader);
		file.close();
	}
	else
	{
		return -1;
	}
	
	GLuint geometryShader = 0;
	if (GeometricString != "")
	{
		file.open(GeometricString, std::ios::in);
		if (file.is_open())
		{
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			std::copy(
				std::istream_iterator<char>(file),
				std::istream_iterator<char>(),
				std::insert_iterator<std::string>(str, str.begin()));
			const GLchar* textshader = (const GLchar*)str.c_str();
			glShaderSource(geometryShader, 1, &textshader, 0);
			glCompileShader(geometryShader);
			file.close();
		}
	}
	file.open(FragmentString, std::ios::in);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (file.is_open())
	{
		std::copy(
			std::istream_iterator<char>(file),
			std::istream_iterator<char>(),
			std::insert_iterator<std::string>(str, str.begin()));
		const GLchar* textshader = (const GLchar*)str.c_str();
		glShaderSource(fragmentShader, 1, &textshader, 0);
		glCompileShader(fragmentShader);
		file.close();
	}
	else
	{
		return -1;// при таком исключении не будет удалятся Vertex(GEOMETRY) шейдер
	}
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	if (GeometricString != "")
	{
		glAttachShader(program, geometryShader);
	}
	glLinkProgram(program);

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	if (GeometricString != "")
	{
		glDetachShader(program, geometryShader);
		glDeleteProgram(geometryShader);
	}
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader);
	return program;
}

int init(GLFWwindow** window)
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

	*window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (*window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(*window);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	std::string VertexShader = "Components\\Shaders\\vertexShader_c.vert";
	std::string FragentShader = "Components\\Shaders\\fragmentShader.frag";
	if (_program_contour = _program = CompileShaders(VertexShader, FragentShader) == -1)
	{
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(*window, &width, &height);
	glfwSetKeyCallback(*window, key_callback);
	glViewport(0, 0, width, height);

	_renderObjects.push_back(RenderObject(CreateSolidCube(0.5, 0.0, 2.0, 0.0), new GLint[4]{ 240 ,128 ,128, 255 }, new GLint[4]{ 240 ,128 ,128, 255 }));
	for (int i = 0; i < 20; i++)
	{
		_renderObjects.push_back(RenderObject(CreateSolidCube(0.5f, 1, 12.0f - (float)i, 0.0f), new GLint[4]{ 240 ,128 ,128, 255 }, new GLint[4]{ 240 ,128 ,128, 255 }));
	}
}

int main()
{
	GLFWwindow* window;
	if (init(&window) == -1)
	{
		return -1;
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(_program);
		for(int i = 0; i < _renderObjects.size(); i++)
		{
			Render_figure(_renderObjects[i], GL_FILL);
			const GLint* color = { _renderObjects[i].color_obj };
			glUniform4iv(19, 4, color);
			_renderObjects[i].Render();
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();

	return 0;
}