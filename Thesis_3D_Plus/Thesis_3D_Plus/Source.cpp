#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Vertex.h"
#include "RenderObject.h"
#include "Camera.h"
#include "GLWindow.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc/type_ptr.hpp>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/FL_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <ctime>


//std::vector<RenderObject> _renderObjects;
//std::vector<glm::vec4> color4s_unique;
//int _program_contour, _program;
//int _SelectID = -1;
//Camera camera1 = Camera();
//int width, height;
//glm::mat4x4 _projectionMatrix;
//glm::mat4x4 _modelView;
//glm::mat4x4 _view;
//glm::vec2 lastMousePos = glm::vec2(30.0f, 140.0f);
//
//float angle = 90.0f;

GLWindow *glWindow = new GLWindow(10, 10, 800, 600);
Fl_Float_Input *x_input;
Fl_Float_Input *y_input;
Fl_Float_Input *z_input;

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
//	// и приложение после этого закроется
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	switch (key)
//	{
//	case GLFW_KEY_W:
//		camera1.Move(0, 1.5f, 0);
//		break;
//	case GLFW_KEY_S:
//		camera1.Move(0, -1.5f, 0);
//		break;
//	case GLFW_KEY_A:
//		camera1.Move(-1.5f, 0.0f, 0);
//		break;
//	case GLFW_KEY_D:
//		camera1.Move(1.5f, 0, 0);
//		break;
//	case GLFW_KEY_Q:
//		camera1.Move(0, 0, 1.5f);
//		break;
//	case GLFW_KEY_E:
//		camera1.Move(0, 0, -1.5f);
//		break;
//	case GLFW_KEY_J:
//		camera1.AddRotation(10.0f, 0.0f);
//		break;
//	case GLFW_KEY_L:
//		camera1.AddRotation(-10.0f, 0.0f);
//		break;
//	case GLFW_KEY_I:
//		camera1.AddRotation(0.0f, 10.0f);
//		break;
//	case GLFW_KEY_K:
//		camera1.AddRotation(0.0f, -10.0f);
//		break;
//	}
//	if (action == GLFW_REPEAT || action == GLFW_PRESS)
//	{
//		switch (key)
//		{
//		case GLFW_KEY_8:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(1, 0, 0));
//			}
//			break;
//		case GLFW_KEY_6:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 0, 1));
//			}
//			break;
//		case GLFW_KEY_4:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 0, -1));
//			}
//			break;
//		case GLFW_KEY_2:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(-1, 0, 0));
//			}
//			break;
//		case GLFW_KEY_7:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, -1, 0));
//			}
//			break;
//		case GLFW_KEY_9:
//			if (_SelectID > -1)
//			{
//				_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 1, 0));
//			}
//			break;
//		}
//	}
//}
//
//glm::vec4 RandomColor()//Потом переделаю
//{
//	glm::vec4 temp_color = glm::vec4(0, 0, 0, 1);
//	bool flag = true;
//	while (flag)
//	{
//		flag = false;
//		temp_color = glm::vec4(rand()% 256, rand() % 256, rand() % 256, rand() % 256);
//		for (int i = 0; i < color4s_unique.size() && flag; i++)
//		{
//			if (temp_color == color4s_unique[i] || temp_color == glm::vec4(0, 0, 0, 1))
//			{
//				flag = true;
//			}
//		}
//		if (!flag)
//		{
//			color4s_unique.push_back(temp_color);
//		}
//	}
//	return temp_color;
//}
//
//void CreateProjection()
//{
//	float aspectRatio = (float)width / height;
//	_projectionMatrix = glm::perspective(glm::radians(angle), aspectRatio, 0.1f, 100.0f);
//	glUniformMatrix4fv(21, 1, false, glm::value_ptr(_projectionMatrix));
//	_modelView = camera1.GetViewMatrix();
//	_view = _projectionMatrix * _modelView;
//
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	CreateProjection();
//	glLoadIdentity();
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//	std::string title = "Thesis_3D_Plus " + std::to_string(width) + "x" + std::to_string(height);
//	glfwSetWindowTitle(window, title.c_str());
//	title.clear();
//	// Re-render the scene because the current frame was drawn for the old resolution
//}
//
//void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	glm::vec2 delta = lastMousePos - glm::vec2(xpos, ypos);
//	camera1.AddRotation(delta.x, delta.y);
//	lastMousePos = glm::vec2(xpos, ypos);
//}
//
//void Render_figure(RenderObject renderObject, GLint polygonMode)
//{
//	renderObject.Bind();
//	glUniformMatrix4fv(20, 1, false, glm::value_ptr(_view));
//	glUniformMatrix4fv(22, 1, false, glm::value_ptr(renderObject.ModelMatrix));
//	renderObject.PolygonMode_now(polygonMode);
//}
//
//void Render_select_color_buf()
//{
//	CreateProjection();
//	glUniformMatrix4fv(21, 1, false, glm::value_ptr(_projectionMatrix));
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glUseProgram(_program_contour);
//	glm::vec4 temp_color;
//	for (std::vector<RenderObject>::iterator it = _renderObjects.begin(); it != _renderObjects.end(); it++)
//	{
//		int iter = std::distance(_renderObjects.begin(), it);
//		temp_color.r = color4s_unique[iter].r / 255;
//		temp_color.g = color4s_unique[iter].g / 255;
//		temp_color.b = color4s_unique[iter].b / 255;
//		temp_color.a = color4s_unique[iter].a / 255;
//		Render_figure(*it, GL_FILL);
//
//		glUniform4fv(19, 1, glm::value_ptr(temp_color));
//		(*it).Render();
//	}
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		GLuint colorFBO;
//		glGenBuffers(1, &colorFBO);
//		glBindFramebuffer(GL_FRAMEBUFFER, colorFBO);
//		{
//			_SelectID = -1;
//			glEnable(GL_DEPTH_TEST);
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//			unsigned char pixel[4];
//			Render_select_color_buf();
//			int width, height;
//			glfwGetWindowSize(window, &width, &height);
//			glReadPixels(lastMousePos.x, height - lastMousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);
//			
//			glm::vec4 temp_color;
//			temp_color.r = pixel[0];
//			temp_color.g = pixel[1];
//			temp_color.b = pixel[2];
//			temp_color.a = pixel[3];
//			for (int i = 0; i < _renderObjects.size(); i++)
//			{
//				if (color4s_unique[i] == temp_color)
//				{
//					_SelectID = i;
//				}
//			}
//		}
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	}
//}
//
//GLuint CompileShaders(std::string VertexString, std::string FragmentString, std::string GeometricString = "")
//{
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	std::string str;
//	std::ifstream file(VertexString);
//	if (file.is_open())
//	{
//		std::stringstream str_stream;
//		str_stream << file.rdbuf();
//		char* textshader = new char[1+str_stream.str().size()];
//		const GLint lenhader = (GLint)str_stream.str().length();
//		strcpy_s(textshader, 1 + lenhader, str_stream.str().c_str());
//		std::cout << textshader << std::endl;
//		glShaderSource(vertexShader, 1, &textshader, &lenhader);
//		glCompileShader(vertexShader);
//		file.close();
//		delete(textshader);
//	}
//	else
//	{
//		return -1;
//	}
//	GLint Result = GL_FALSE;
//	int InfoLogLength;
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
//		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//		fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
//		return -1;
//	}
//	GLuint geometryShader = 0;
//	if (GeometricString != "")
//	{
//		file.open(GeometricString, std::ios::in);
//		if (!file && file.is_open())
//		{
//			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
//			std::stringstream str_stream;
//			str_stream << file.rdbuf();
//			char* textshader = new char[1 + str_stream.str().size()];
//			const GLint lenhader = (GLint)(1 + str_stream.str().size());
//			strcpy_s(textshader, 1 + str_stream.str().size(), str_stream.str().c_str());
//			std::cout << textshader << std::endl;
//			glShaderSource(geometryShader, 1, &textshader, &lenhader);
//			glCompileShader(geometryShader);
//			file.close();
//			delete(textshader);
//			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &Result);
//			glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
//			if (InfoLogLength > 0) {
//				std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
//				glGetShaderInfoLog(geometryShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//				fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
//			}
//		}
//	}
//	file.open(FragmentString, std::ios::in);
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	if (file.is_open())
//	{
//		std::stringstream str_stream;
//		str_stream << file.rdbuf();
//		char* textshader = new char[1 + str_stream.str().size()];
//		const GLint lenhader = (GLint)str_stream.str().length();
//		strcpy_s(textshader, 1 +lenhader, str_stream.str().c_str());
//		std::cout << textshader << std::endl;
//		glShaderSource(fragmentShader, 1, &textshader, &lenhader);
//		glCompileShader(fragmentShader);
//		delete(textshader);
//		file.close();
//	}
//	else
//	{
//		return -1;// при таком исключении не будет удалятся Vertex(GEOMETRY) шейдер
//	}
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
//		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//		fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
//		return -1;
//	}
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vertexShader);
//	glAttachShader(program, fragmentShader);
//	if (GeometricString != "")
//	{
//		glAttachShader(program, geometryShader);
//	}
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &Result);
//	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
//		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
//		return -1;
//	}
//	glDetachShader(program, vertexShader);
//	glDetachShader(program, fragmentShader);
//	if (GeometricString != "")
//	{
//		glDetachShader(program, geometryShader);
//		glDeleteProgram(geometryShader);
//	}
//	glDeleteProgram(vertexShader);
//	glDeleteProgram(fragmentShader);
//	return program;
//}
//
//int init(GLFWwindow** window)
//{
//	//Инициализация GLFW
//	glfwInit();
//	//Настройка GLFW
//	//Задается минимальная требуемая версия OpenGL. 
//	//Мажорная 
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	//Минорная
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//Установка профайла для которого создается контекст
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//Выключение возможности изменения размера окна
//	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
//
//	*window = glfwCreateWindow(800, 600, "Thesis_3D_Plus", nullptr, nullptr);
//	if (*window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(*window);
//	glewExperimental = GL_TRUE;
//	GLenum err = glewInit();
//	if (err != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//	
//	std::string VertexShader = ".\\Components\\Shaders\\vertexShader_c.vert";
//	std::string FragentShader = ".\\Components\\Shaders\\fragmentShader.frag";
//	if ((_program_contour = _program = CompileShaders(VertexShader, FragentShader)) == -1)
//	{
//		return -1;
//	}
//	glfwSetCursorPosCallback(*window, mouse_move_callback);
//	glfwSetMouseButtonCallback(*window, mouse_button_callback);
//	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
//	glfwGetFramebufferSize(*window, &width, &height);
//	glfwSetKeyCallback(*window, key_callback);
//	glViewport(0, 0, width, height);
//	std::string title = "Thesis_3D_Plus " + std::to_string(width) + "x" + std::to_string(height);
//	glfwSetWindowTitle(*window, title.c_str());
//	CreateProjection();
//	//_renderObjects.push_back(RenderObject(CreateSolidCube(10.5, 0.0, 2.0, 0.0), new float[4]{ 1.0f ,0.5f ,0.5f, 1 }, new GLint[4]{ 240 ,128 ,128, 255 }));
//	std::vector<Vertex> new_coord_obj = CreateSolidCube(0.5, 0.0, 2.0, 0.0);
//	RenderObject new_obj = RenderObject(new_coord_obj, glm::vec4(1.0f, 0.5f, 0.5f, 1), glm::vec4(1.0f, 0.5f, 0.5f, 1));
//	RandomColor();
//	_renderObjects.push_back(new_obj);
//	new_coord_obj.clear();
//	for (int i = 0; i < 20; i++)
//	{
//		new_coord_obj = CreateSolidCube(0.5f, 1, 12.0f - (float)i, 0.0f);
//		RandomColor();
//		new_obj = RenderObject(new_coord_obj, glm::vec4(1.0f, 0.5f, 0.5f, 1), glm::vec4(1.0f, 0.5f, 0.5f, 1));
//		_renderObjects.push_back(new_obj);
//		new_coord_obj.clear();
//	}
//	title.clear();
//	VertexShader.clear();
//	FragentShader.clear();
//	return 0;
//}

void move_button_click(Fl_Widget *button, void *value) {
	char key = (char)value;
	switch (key)
	{
		case 'w':
			glWindow->camera1.Move(0, 1.5f, 0);
			break;
		case 's':
			glWindow->camera1.Move(0, -1.5f, 0);
			break;
		case 'a':
			glWindow->camera1.Move(-1.5f, 0.0f, 0);
			break;
		case 'd':
			glWindow->camera1.Move(1.5f, 0, 0);
			break;
		case 'q':
			glWindow->camera1.Move(0, 0, 1.5f);
			break;
		case 'e':
			glWindow->camera1.Move(0, 0, -1.5f);
			break;
		case 'j':
			glWindow->camera1.AddRotation(10.0f, 0.0f);
			break;
		case 'l':
			glWindow->camera1.AddRotation(-10.0f, 0.0f);
			break;
		case 'i':
			glWindow->camera1.AddRotation(0.0f, 10.0f);
			break;
		case 'k':
			glWindow->camera1.AddRotation(0.0f, -10.0f);
			break;
		case 'c':
			glWindow->CameraRotationEnable = glWindow->CameraRotationEnable ? false : true;
			break;
		case 'b':
			glWindow->EnableContur = glWindow->EnableContur ? false : true;
			break;
		case 'n':
			glWindow->EnableLight = glWindow->EnableLight ? false : true;
			break;
		default:
		break;
	}
	
	glWindow->redraw();
}

void ok_set_coord_button_click(Fl_Widget *button, void *value)
{
	Fl_Float_Input *set_coord_x_input = ((Fl_Float_Input *)x_input);
	Fl_Float_Input *set_coord_y_input = ((Fl_Float_Input *)y_input);
	Fl_Float_Input *set_coord_z_input = ((Fl_Float_Input *)z_input);
	float x = atof(set_coord_x_input->value());
	float y = atof(set_coord_y_input->value());
	float z = atof(set_coord_z_input->value());
	
	glWindow->camera1.Position = glm::vec3(x, y, z);
	glWindow->redraw();
}
void choice_shader(Fl_Widget *choice, void *userdata)
{
	Fl_Input_Choice *choice_shader = (Fl_Input_Choice*)choice;
	int choice_index = choice_shader->menubutton()->value();
	glWindow->_program = glWindow->ProgramShaders[choice_index];
}

int main(int argc, char **argv)
{
	srand(time(0));
	//GLFWwindow* window;
	//if (init(&window) == -1)
	//{
	//	getchar(); //вместо паузы
	//	return -1;
	//}
	//while (!glfwWindowShouldClose(window))
	//{
	//	glfwPollEvents();
	//	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	for(int i = 0; i < _renderObjects.size(); i++)
	//	{
	//		CreateProjection();
	//		glUseProgram(_program);
	//		Render_figure(_renderObjects[i], GL_FILL);
	//		glUniform4fv(19, 1, glm::value_ptr(_renderObjects[i].color_obj));
	//		_renderObjects[i].Render();
	//		glUseProgram(0);
	//		glUseProgram(_program_contour);
	//		if (_SelectID > -1)
	//		{
	//			glLineWidth(7);
	//			Render_figure(_renderObjects[_SelectID], GL_LINE);
	//			glm::vec4 color = glm::vec4(0, 0, 0, 255);
	//			glUniform4fv(19, 1, glm::value_ptr(color));
	//			_renderObjects[_SelectID].Render_line();
	//		}
	//		glUseProgram(0);
	//	}
	//	glfwSwapBuffers(window);
	//}
	//glfwTerminate();
	//
	//for (int i = 0; i < _renderObjects.size(); i++)
	//{
	//	_renderObjects[i].clear();
	//}
	//std::vector<RenderObject>().swap(_renderObjects);
	//_renderObjects.clear();
	//color4s_unique.clear();
	//camera1.~Camera();

	Fl::use_high_res_GL(1);
	Fl_Window *Flwindow = new Fl_Window(1030, 620);
	Fl_Box *lblMoveCamera = new Fl_Box(860, 20, 90, 20, "Moving camera");
	lblMoveCamera->labelsize(12);
	Fl_Button *q_button = new Fl_Button(860, 45, 30, 25, "Q");
	Fl_Button *w_button = new Fl_Button(900, 45, 30, 25, "W");
	Fl_Button *e_button = new Fl_Button(940, 45, 30, 25, "E");
	Fl_Button *a_button = new Fl_Button(860, 75, 30, 25, "A");
	Fl_Button *s_button = new Fl_Button(900, 75, 30, 25, "S");
	Fl_Button *d_button = new Fl_Button(940, 75, 30, 25, "D");	q_button->callback((Fl_Callback *)move_button_click, (void *)'q');	q_button->when(FL_WHEN_CHANGED);	w_button->callback((Fl_Callback *)move_button_click, (void *)'w');	w_button->when(FL_WHEN_CHANGED);
	e_button->callback((Fl_Callback *)move_button_click, (void *)'e');	e_button->when(FL_WHEN_CHANGED);
	a_button->callback((Fl_Callback *)move_button_click, (void *)'a');	a_button->when(FL_WHEN_CHANGED);
	s_button->callback((Fl_Callback *)move_button_click, (void *)'s');	s_button->when(FL_WHEN_CHANGED);
	d_button->callback((Fl_Callback *)move_button_click, (void *)'d');	d_button->when(FL_WHEN_CHANGED);
	Fl_Box *lblRotationCamera = new Fl_Box(860, 105, 90, 20, "Rotation camera");
	lblRotationCamera->labelsize(12);
	Fl_Button *up_button = new Fl_Button(900, 130, 37, 25, "Up");
	Fl_Button *left_button = new Fl_Button(855, 160, 37, 25, "Left");
	Fl_Button *down_button = new Fl_Button(900, 160, 37, 25, "Down");
	Fl_Button *right_button = new Fl_Button(945, 160, 37, 25, "Right");
	up_button->callback((Fl_Callback *)move_button_click, (void *)'i');	up_button->when(FL_WHEN_CHANGED);
	left_button->callback((Fl_Callback *)move_button_click, (void *)'j');	left_button->when(FL_WHEN_CHANGED);
	down_button->callback((Fl_Callback *)move_button_click, (void *)'k');	down_button->when(FL_WHEN_CHANGED);
	right_button->callback((Fl_Callback *)move_button_click, (void *)'l');	right_button->when(FL_WHEN_CHANGED);
	Fl_Box *lblSetCoordCamera = new Fl_Box(860, 190, 120, 20, "Set camera coordinates");
	lblSetCoordCamera->labelsize(12);
	x_input = new Fl_Float_Input(870, 210, 130, 25, "x:");
	y_input = new Fl_Float_Input(870, 240, 130, 25, "y:");
	z_input = new Fl_Float_Input(870, 270, 130, 25, "z:");
	x_input->maximum_size(15);
	y_input->maximum_size(15);
	z_input->maximum_size(15);
	Fl_Button *ok_set_coord_button = new Fl_Button(870, 300, 35, 25, "Ok");
	ok_set_coord_button->callback((Fl_Callback *)ok_set_coord_button_click);	ok_set_coord_button->when(FL_WHEN_CHANGED);
	glWindow->CameraRotationEnable_button = new Fl_Check_Button(867, 330, 150, 25, "Following the cursor");
	(((Fl_Check_Button*)((GLWindow*)glWindow)->CameraRotationEnable_button))->value(true);
	((Fl_Check_Button*)((GLWindow*)glWindow)->CameraRotationEnable_button)->callback((Fl_Callback *)move_button_click, (void *)'c');
	glWindow->EnableContur_button = new Fl_Check_Button(867, 360, 150, 25, "Show Contur");
	(((Fl_Check_Button*)((GLWindow*)glWindow)->EnableContur_button))->value(false);
	((Fl_Check_Button*)((GLWindow*)glWindow)->EnableContur_button)->callback((Fl_Callback *)move_button_click, (void *)'b');
	glWindow->EnableLight_button = new Fl_Check_Button(867, 390, 150, 25, "Show source light");
	(((Fl_Check_Button*)((GLWindow*)glWindow)->EnableLight_button))->value(false);
	((Fl_Check_Button*)((GLWindow*)glWindow)->EnableLight_button)->callback((Fl_Callback *)move_button_click, (void *)'n');
	Fl_Box *lblShaderOptions = new Fl_Box(860, 420, 120, 20, "Shader options");
	lblShaderOptions->labelsize(12);
	lblShaderOptions->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
	glWindow->ShaderOptions = new Fl_Input_Choice(860, 440, 120, 20);
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("Deafult shader");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("P.S. without reflection");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->callback(choice_shader, 0);
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->menubutton()->value(0);
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->value(0);
	Fl_Input *ip = (((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->input();
	ip->readonly(1);
	Fl_Group *Flgroup = new Fl_Group(20, 20, 820, 620);
	Flgroup->add(glWindow);
	Flgroup->end();
	glWindow->end();
	Flwindow->show(argc, argv);
	glWindow->show();
	if (glWindow->InitializeGL() == -1)
	{
		getchar();
		//Здесь должен вызваться деструктор
		return 1;
	}

	while (Fl::run())
	{
		glWindow->redraw();
	}
	while(Fl::wait())
	{
		glWindow->redraw();
	}
	
	return 0;
}