#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
class Camera
{
private:
	
	GLfloat Position[3] = {0.0f, 0.0f, 0.0f};
	GLfloat Orientation[3] = { (float)M_PI, 0.0f, 0.0f };
	float MoveSpeed = 0.05f;
	float MouseSensitivity = 0.01f;
	bool Rotation_status = true;
public:
	Camera();
	~Camera();
};

