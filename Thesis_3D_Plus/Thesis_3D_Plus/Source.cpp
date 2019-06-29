#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include "Vertex.h"
#include "RenderObject.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::vector<RenderObject> _renderObjects;
int _program_contour, _program;
Camera camera1 = Camera();
int width, height;
glm::mat4x4 _projectionMatrix;
glm::mat4x4 _modelView;
glm::mat4x4 _view;
glm::vec2 lastMousePos = glm::vec2(30.0f, 140.0f);
float angle = 90.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void CreateProjection()
{
	float aspectRatio = (float)width / height;
	_projectionMatrix = glm::tweakedInfinitePerspective(angle * (float)M_PI / 180.0f, aspectRatio, 0.01f);
	_modelView = camera1.GetViewMatrix();
	_view = _modelView * _projectionMatrix;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	CreateProjection();

	glLoadIdentity();
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	glUniformMatrix4fv(21, 1, false, glm::value_ptr(_projectionMatrix));
	std::string title = "Thesis_3D_Plus " + std::to_string(width) + "x" + std::to_string(height);
	glfwSetWindowTitle(window, title.c_str());
	// Re-render the scene because the current frame was drawn for the old resolution
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 delta = lastMousePos - glm::vec2(xpos, ypos);
	camera1.AddRotation(delta.x, delta.y);
	lastMousePos = glm::vec2(xpos, ypos);
}

void Render_figure(RenderObject renderObject, GLint polygonMode)
{
	renderObject.Bind();
	glUniformMatrix4fv(20, 1, false, glm::value_ptr(_view));
	glUniformMatrix4fv(22, 1, false, glm::value_ptr(_modelView));
	renderObject.PolygonMode_now(polygonMode);
}

GLuint CompileShaders(std::string VertexString, std::string FragmentString, std::string GeometricString = "")
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string str;
	std::ifstream file(VertexString);
	if (file.is_open())
	{
		std::stringstream str_stream;
		str_stream << file.rdbuf();
		char* textshader = new char[1+str_stream.str().size()];
		strcpy_s(textshader, 1+str_stream.str().size(), str_stream.str().c_str());
		std::cout << str_stream.str().c_str();
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
		if (!file && file.is_open())
		{
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			std::stringstream str_stream;
			str_stream << file.rdbuf();
			char* textshader = new char[1 + str_stream.str().size()];
			strcpy_s(textshader, 1 + str_stream.str().size(), str_stream.str().c_str());
			std::cout << textshader;
			glShaderSource(geometryShader, 1, &textshader, 0);
			glCompileShader(geometryShader);
			file.close();
		}
	}
	file.open(FragmentString, std::ios::in);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (file.is_open())
	{
		std::stringstream str_stream;
		str_stream << file.rdbuf();
		char* textshader = new char[1 + str_stream.str().size()];
		strcpy_s(textshader, 1 + str_stream.str().size(), str_stream.str().c_str());
		std::cout << textshader;
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

	*window = glfwCreateWindow(800, 600, "Thesis_3D_Plus", nullptr, nullptr);
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
	CreateProjection();
	std::string VertexShader = ".\\Components\\Shaders\\vertexShader_c.vert";
	std::string FragentShader = ".\\Components\\Shaders\\fragmentShader.frag";
	if (_program_contour = _program = CompileShaders(VertexShader, FragentShader) == -1)
	{
		return -1;
	}
	glfwSetCursorPosCallback(*window, mouse_move_callback);
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
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
		CreateProjection();
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