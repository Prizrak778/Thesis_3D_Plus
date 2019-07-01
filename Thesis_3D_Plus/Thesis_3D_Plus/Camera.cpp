#include "Camera.h"



glm::mat4x4 Camera::GetViewMatrix()
{
	glm::vec3 lookat;
	lookat.x = sinf(Orientation.x)*cosf(Orientation.y);
	lookat.y = sinf(Orientation.y);
	lookat.z = cosf(Orientation.x)*cosf(Orientation.y);
	glm::vec3 right = glm::vec3(
		sin(Orientation.x - 3.14f / 2.0f),
		0,
		cos(Orientation.x - 3.14f / 2.0f)
	);
	glm::vec3 up = glm::cross(right, lookat);
	return glm::lookAt(Position, Position + lookat, up);
}

void Camera::Move(float x, float y, float z)
{
	glm::vec3 offset = glm::vec3(0, 0, 0);

	glm::vec3 forward = glm::vec3(sinf(Orientation.x), 0 ,cosf(Orientation.x));
	glm::vec3 right = glm::vec3(forward.z, 0, forward.x);

	offset += x * right;
	offset += y * forward;
	offset.y += z;

	glm::normalize(offset);
	offset = offset * MouseSensitivity;

	Position += offset;
}

void Camera::AddRotation(float x, float y)
{
	x = x * MouseSensitivity;
	y = y * MouseSensitivity;
	float _y = (float)M_PI * 2.0f;
	Orientation.x = modff((Orientation.x + x), &_y);
	Orientation.y = glm::max(glm::min(Orientation.y + y, (float)M_PI / 2.0f - 0.1f), (float)-M_PI / 2.0f + 0.1f);
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
