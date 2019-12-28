#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include "Vertex.h"
#include "LightObject.h"
#include "RenderObject.h"
#include "Camera.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input_Choice.H>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <ctime>

#define GLEW_STATIC 1
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

class GLWindow : public Fl_Gl_Window
{
   private: 
	  
   public:
	  GLWindow(int x, int y, int width, int height);
	  GLWindow(int x, int y, int width, int height, char* title);
      virtual ~GLWindow();

      int InitializeGL();
	  void CreateProjection();
	  
	  glm::vec4 RandomColor();
	  void Render_figure(RenderObject renderObject, GLint polygonMode);
	  void Render_select_color_buf();
	  int CompileAllShaders();
	  GLuint CompileShaders(std::string VertexString, std::string FragmentString, std::string GeometricString = "");
	  virtual int handle(int);
      virtual void draw();
	  void findRenderObject(std::vector<LightObject> *light_obj, RenderObject render_obj);

	  int Fl_width;
	  int Fl_height;
	  int _program_contour, _program, _program_some_light;
	  int _SelectID = -1;
	  Camera camera1 = Camera();
	  int width, height;
	  glm::mat4x4 _projectionMatrix;
	  glm::mat4x4 _modelView;
	  glm::mat4x4 _view;
	  glm::vec2 lastMousePos = glm::vec2(30.0f, 140.0f);
	  bool CameraRotationEnable = true;
	  bool EnableContur = false;
	  bool EnableLight = true;
	  float angle = 90.0f;

	  std::vector<RenderObject> _renderObjects;
	  std::vector<LightObject> _lightObjects;
	  std::vector<glm::vec4> color4s_unique;
	  std::vector<int> ProgramShaders;
	 
	  Fl_Check_Button *CameraRotationEnable_button;//Плохое решение как по мне
	  Fl_Check_Button *EnableContur_button;//Плохое решение как по мне
	  Fl_Check_Button *EnableLight_button;//Плохое решение как по мне
	  Fl_Input_Choice *ShaderOptions;
	  Fl_Box *lblFps;
};
#endif
