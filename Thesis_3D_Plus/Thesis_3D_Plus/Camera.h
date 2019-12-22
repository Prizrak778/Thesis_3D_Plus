#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_transform.inl>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
class Camera
{
private:
	double pi = 3.14159265358979323846;
	
	glm::vec3 Orientation = { (float)pi, 0.0f, 0.0f };
	float MoveSpeed = 0.5f;
	float MouseSensitivity = 0.01f;
	bool Rotation_status = true;
public:
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	glm::mat4x4 GetViewMatrix();
	void Move(float x, float y, float z);
	void AddRotation(float x, float y);
	Camera();
	~Camera();
};

