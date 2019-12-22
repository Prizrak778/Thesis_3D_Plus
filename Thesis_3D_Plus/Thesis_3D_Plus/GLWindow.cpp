#include "GLWindow.h"


GLWindow::GLWindow(int x, int y, int width, int height) : Fl_Gl_Window(x, y, width, height)
{
	mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE| FL_OPENGL3);
	Fl_width = width;
	Fl_height = height;
}

GLWindow::GLWindow(int x, int y, int width, int height, char* title) : Fl_Gl_Window(x, y, width, height, title)
{
	mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE | FL_OPENGL3);
	Fl_width = width;
	Fl_height = height;
}



GLWindow::~GLWindow()
{
	//Здесь должен вызываться деструктер для внутренних компонентов за исключением контролов 
}

int GLWindow::CompileAllShaders()
{
	std::string VertexShader = ".\\Components\\Shaders\\vertexShader_c.vert";
	std::string FragentShader = ".\\Components\\Shaders\\fragmentShader.frag";
	if ((_program = _program_contour = CompileShaders(VertexShader, FragentShader)) == -1)
	{
		std::cout << "Default shader failed" << std::endl;
		return -1;
	}
	ProgramShaders.push_back(_program);
	VertexShader = ".\\Components\\Shaders\\vertexShader.vert";
	FragentShader = ".\\Components\\Shaders\\fragmentShader.frag";
	if ((_program = CompileShaders(VertexShader, FragentShader)) == -1)
	{
		std::cout << "P.S. without reflection shader failed" << std::endl;
		return -1;
	}
	ProgramShaders.push_back(_program);
	_program = ProgramShaders[0];
	VertexShader.clear();
	FragentShader.clear();
	return 0;
}

GLuint GLWindow::CompileShaders(std::string VertexString, std::string FragmentString, std::string GeometricString)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string str;
	std::ifstream file(VertexString);
	if (file.is_open())
	{
		std::stringstream str_stream;
		str_stream << file.rdbuf();
		char* textshader = new char[1 + str_stream.str().size()];
		const GLint lenhader = (GLint)str_stream.str().length();
		strcpy_s(textshader, 1 + lenhader, str_stream.str().c_str());
		std::cout << textshader << std::endl;
		glShaderSource(vertexShader, 1, &textshader, &lenhader);
		glCompileShader(vertexShader);
		file.close();
		delete(textshader);
	}
	else
	{
		std::cout << "GL_VERTEX_SHADER file is not open" << std::endl;
		return -1;
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
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
			const GLint lenhader = (GLint)(1 + str_stream.str().size());
			strcpy_s(textshader, 1 + str_stream.str().size(), str_stream.str().c_str());
			std::cout << textshader << std::endl;
			glShaderSource(geometryShader, 1, &textshader, &lenhader);
			glCompileShader(geometryShader);
			file.close();
			delete(textshader);
			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
				glGetShaderInfoLog(geometryShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
				fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
			}
		}
		else
		{
			std::cout << "GL_GEOMETRY_SHADER file is not open" << std::endl;
			return -1;
		}
	}
	file.open(FragmentString, std::ios::in);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (file.is_open())
	{
		std::stringstream str_stream;
		str_stream << file.rdbuf();
		char* textshader = new char[1 + str_stream.str().size()];
		const GLint lenhader = (GLint)str_stream.str().length();
		strcpy_s(textshader, 1 + lenhader, str_stream.str().c_str());
		std::cout << textshader << std::endl;
		glShaderSource(fragmentShader, 1, &textshader, &lenhader);
		glCompileShader(fragmentShader);
		delete(textshader);
		file.close();
	}
	else
	{
		std::cout << "GL_FRAGMENT_SHADER file is not open" << std::endl;
		return -1;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
		return -1;
	}
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	if (GeometricString != "")
	{
		glAttachShader(program, geometryShader);
	}
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		return -1;
	}
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

glm::vec4 GLWindow::RandomColor()//Потом переделаю
{
	glm::vec4 temp_color = glm::vec4(0, 0, 0, 1);
	bool flag = true;
	while (flag)
	{
		flag = false;
		temp_color = glm::vec4(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		for (int i = 0; i < color4s_unique.size() && flag; i++)
		{
			if (temp_color == color4s_unique[i] || temp_color == glm::vec4(0, 0, 0, 1))
			{
				flag = true;
			}
		}
		if (!flag)
		{
			color4s_unique.push_back(temp_color);
		}
	}
	return temp_color;
}

int GLWindow::InitializeGL()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	const uchar *glsv = glGetString(GL_SHADING_LANGUAGE_VERSION);
	const uchar *glv = glGetString(GL_VERSION);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	std::string VertexShader = ".\\Components\\Shaders\\vertexShader_c.vert";
	std::string FragentShader = ".\\Components\\Shaders\\fragmentShader.frag";
	if (CompileAllShaders() == -1)
	{
		return -1;
	}
	
	VertexShader.clear();
	FragentShader.clear();
	CreateProjection();
	glm::vec3 position_obj = glm::vec3(0.0, 2.0, 0.0);
	std::vector<Vertex> new_coord_obj = CreateSolidCube(0.5, position_obj);
	RenderObject new_obj = RenderObject(new_coord_obj, position_obj, glm::vec4(1.0f, 0.5f, 0.5f, 1), RandomColor());
	_renderObjects.push_back(new_obj);
	new_coord_obj.clear();
	for (int i = 0; i < 20; i++)
	{
		position_obj = glm::vec3(1, 12.0f - (float)i, 0.0f);
		new_coord_obj = CreateSolidCube(0.5f, position_obj);
		new_obj = RenderObject(new_coord_obj, position_obj, glm::vec4(1.0f, 0.5f, 0.5f, 1), RandomColor());
		_renderObjects.push_back(new_obj);
		new_coord_obj.clear();
	}
	position_obj = glm::vec3(-1.0, 2.0, 0.0);
	new_coord_obj = CreateSolidCube(0.5, position_obj);
	LightObject new_light = LightObject(new_coord_obj, glm::vec4(1.0f, 1.0f, 0.0f, 1), RandomColor(), position_obj, glm::vec4(5.0f, 5.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 5.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 5.0f));
	_lightObjects.push_back(new_light);
	_renderObjects.push_back(new_light.LightRenderObject);
	new_coord_obj.clear();
	return 0;
}
void GLWindow::CreateProjection()
{
	float aspectRatio = (float)Fl_width / Fl_height;
	_projectionMatrix = glm::perspective(glm::radians(angle), aspectRatio, 0.1f, 100.0f);
	glUniformMatrix4fv(21, 1, false, glm::value_ptr(_projectionMatrix));
	_modelView = camera1.GetViewMatrix();
	_view = _projectionMatrix * _modelView;

}

void GLWindow::Render_figure(RenderObject renderObject, GLint polygonMode)
{
	renderObject.Bind();
	glUniformMatrix4fv(20, 1, false, glm::value_ptr(_view));
	glUniformMatrix4fv(22, 1, false, glm::value_ptr(renderObject.ModelMatrix));
	renderObject.PolygonMode_now(polygonMode);
}

void GLWindow::Render_select_color_buf()
{
	CreateProjection();
	glUniformMatrix4fv(21, 1, false, glm::value_ptr(_projectionMatrix));
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glUseProgram(_program_contour);
	glm::vec4 temp_color;
	for (std::vector<RenderObject>::iterator it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		int iter = std::distance(_renderObjects.begin(), it);
		temp_color.r = color4s_unique[iter].r / 255;
		temp_color.g = color4s_unique[iter].g / 255;
		temp_color.b = color4s_unique[iter].b / 255;
		temp_color.a = color4s_unique[iter].a / 255;
		Render_figure(*it, GL_FILL);

		glUniform4fv(19, 1, glm::value_ptr(temp_color));
		(*it).Render();
	}
}

void GLWindow::draw()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < _renderObjects.size(); i++)
	{

		CreateProjection();
		glUseProgram(_program_contour);
		if (EnableContur)
		{
			glLineWidth(2);
			Render_figure(_renderObjects[i], GL_LINE);
			glm::vec4 color = glm::vec4(0, 0, 0, 255);
			glUniform4fv(19, 1, glm::value_ptr(color));
			_renderObjects[i].Render_line();
		}

		CreateProjection();
		glUseProgram(_program);
		Render_figure(_renderObjects[i], GL_FILL);
		glUniform4fv(19, 1, glm::value_ptr(_renderObjects[i].color_obj));
		for(int j = 0; j < _lightObjects.size(); j++)//Кривое решение
		{
			_lightObjects[j].PositionLightUniform(18);
		}
		_renderObjects[i].Render();

		CreateProjection();
		glUseProgram(_program_contour);
		if (_SelectID > -1)
		{
			glLineWidth(7);
			Render_figure(_renderObjects[_SelectID], GL_LINE);
			glm::vec4 color = glm::vec4(0, 0, 0, 255);
			glUniform4fv(19, 1, glm::value_ptr(color));
			_renderObjects[_SelectID].Render_line();
		}
		glUseProgram(0);
	}
}

void GLWindow::findRenderObject(std::vector<LightObject> *light_obj, RenderObject render_obj)
{
	for (std::vector<LightObject>::iterator it = (*light_obj).begin(); it != (*light_obj).end(); it++)
	{
		if ((*it).LightRenderObject.color_choice == render_obj.color_choice)
		{
			(*it).LightRenderObject = render_obj;
		}
	}
}

int GLWindow::handle(int event) {
	static int first = 1;
	switch (event) {
		case FL_SHORTCUT:
		{
			const char *key = Fl::event_text();
			char key_text = (char)*key;
			switch (key_text)
			{
			case 'w':
				camera1.Move(0, 1.5f, 0);
				break;
			case 's':
				camera1.Move(0, -1.5f, 0);
				break;
			case 'a':
				camera1.Move(-1.5f, 0.0f, 0);
				break;
			case 'd':
				camera1.Move(1.5f, 0, 0);
				break;
			case 'q':
				camera1.Move(0, 0, 1.5f);
				break;
			case 'e':
				camera1.Move(0, 0, -1.5f);
				break;
			case 'j':
				camera1.AddRotation(10.0f, 0.0f);
				break;
			case 'l':
				camera1.AddRotation(-10.0f, 0.0f);
				break;
			case 'i':
				camera1.AddRotation(0.0f, 10.0f);
				break;
			case 'k':
				camera1.AddRotation(0.0f, -10.0f);
				break;
			case 'c':
				if (CameraRotationEnable)
				{
					CameraRotationEnable_button->value(false);
					CameraRotationEnable = false;
				}
				else
				{
					CameraRotationEnable_button->value(true);
					CameraRotationEnable = true;
				}
				break;
			case 'b':
				if (EnableContur)
				{
					EnableContur_button->value(false);
					EnableContur = false;
				}
				else
				{
					EnableContur_button->value(true);
					EnableContur = true;
				}
				break;
			case 'n':
				if (EnableLight)
				{
					EnableLight_button->value(false);
					EnableLight = false;
				}
				else
				{
					EnableLight_button->value(true);
					EnableLight = true;
				}
				break;
			default:
				break;
			}
			if (_SelectID > -1)
			{
				bool not_default_key = true;
				switch (key_text)
				{
					case '8':
						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0.25, 0, 0));

						break;
					case '6':

						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 0, 0.25));

						break;
					case '4':

						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 0, -0.25));

						break;
					case '2':

						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(-0.25, 0, 0));

						break;
					case '7':

						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, -0.25, 0));

						break;
					case '9':

						_renderObjects[_SelectID].changeModelMstrix(glm::vec3(0, 0.25, 0));

						break;
					default:
						not_default_key = false;
						break;
				}
				if (not_default_key && _renderObjects[_SelectID].TybeObject == LightSourceObject)
				{
					findRenderObject(&_lightObjects, _renderObjects[_SelectID]);
				}
			}
			redraw();
			return Fl_Gl_Window::handle(event);
		}
		case FL_SHOW:
		{
			if (first && shown())
			{
				first = 0;
				make_current();
			}
			return Fl_Gl_Window::handle(event);
		}
		case FL_MOVE:
		{
			if (CameraRotationEnable)
			{
				int xpos = Fl::event_x();
				int ypos = Fl::event_y();
				//Fl::get_mouse(xpos, ypos);
				glm::vec2 delta = lastMousePos - glm::vec2(xpos, ypos);
				camera1.AddRotation(delta.x, delta.y);
				lastMousePos = glm::vec2(xpos, ypos);
				redraw();
				std::cout << xpos << " " << ypos << " " << delta.x << " " << delta.y << std::endl;
			}
			return Fl_Gl_Window::handle(event);
		}
		case FL_PUSH:
			//... mouse down event ...
			//... position in Fl::event_x() and Fl::event_y()
			GLuint colorFBO;
			glGenBuffers(1, &colorFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, colorFBO);
			{
				_SelectID = -1;
				glEnable(GL_DEPTH_TEST);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				unsigned char pixel[4];
				Render_select_color_buf();
				glReadPixels(lastMousePos.x, Fl_height - lastMousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);

				glm::vec4 temp_color;
				temp_color.r = pixel[0];
				temp_color.g = pixel[1];
				temp_color.b = pixel[2];
				temp_color.a = pixel[3];
				for (int i = 0; i < _renderObjects.size(); i++)
				{
					if (color4s_unique[i] == temp_color)
					{
						_SelectID = i;
					}
				}
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return Fl_Gl_Window::handle(event);
		case FL_DRAG:
			//... mouse moved while down event ...
			return Fl_Gl_Window::handle(event);
		case FL_RELEASE:
			//... mouse up event ...
			return Fl_Gl_Window::handle(event);
		case FL_FOCUS:
		case FL_UNFOCUS:
			//... Return 1 if you want keyboard events, 0 otherwise
			return Fl_Gl_Window::handle(event);
		case FL_KEYBOARD:
			//... keypress, key is in Fl::event_key(), ascii in Fl::event_text()
			//... Return 1 if you understand / use the keyboard event, 0 otherwise..
			const char *key = Fl::event_text();
			std::cout << key << std::endl;
			return Fl_Gl_Window::handle(event);
	}
	return Fl_Gl_Window::handle(event);
}
