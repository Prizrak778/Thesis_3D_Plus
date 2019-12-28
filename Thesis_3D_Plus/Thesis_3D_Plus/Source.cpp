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

GLWindow *glWindow = new GLWindow(10, 10, 800, 600);
Fl_Float_Input *x_input;
Fl_Float_Input *y_input;
Fl_Float_Input *z_input;

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
	glWindow->redraw();
}

int main(int argc, char **argv)
{
	srand(time(0));
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
	(((Fl_Check_Button*)((GLWindow*)glWindow)->EnableLight_button))->value(true);
	((Fl_Check_Button*)((GLWindow*)glWindow)->EnableLight_button)->callback((Fl_Callback *)move_button_click, (void *)'n');
	Fl_Box *lblShaderOptions = new Fl_Box(860, 420, 120, 20, "Shader options");
	lblShaderOptions->labelsize(12);
	lblShaderOptions->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
	glWindow->lblFps = new Fl_Box(860, 600, 120, 20, "FPS:");
	((Fl_Box*)((GLWindow*)glWindow)->lblFps)->labelsize(12);
	((Fl_Box*)((GLWindow*)glWindow)->lblFps)->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
	glWindow->ShaderOptions = new Fl_Input_Choice(860, 440, 120, 20);
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("Deafult shader");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("P.S. without reflection");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("P.S. with reflection"); 
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("P.S. with double reflection");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("P.S. with flat shadow");
	(((Fl_Input_Choice*)((GLWindow*)glWindow)->ShaderOptions))->add("Some P.S.");
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

	while(Fl::wait())
	{
		glWindow->redraw();
	}
	//Здесь должен вызваться деструктор
	return 0;
}