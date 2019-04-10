#include "Camera.h"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"

void Camera::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::MovePosition(glm::vec3 movePosition)
{
	position += movePosition;
	Reset();
}

void Camera::MovePosition(float x, float y, float z)
{
	MovePosition(glm::vec3(x,y,z));
}

void Camera::SetDirection(glm::vec3 newDirection)
{
	direction = newDirection;
	Reset();
}

glm::vec3 Camera::GetDirection()
{
	return direction;
}

void Camera::SetTargetPosition(glm::vec3 newTargetPosition)
{
	SetDirection(glm::normalize(position - newTargetPosition));
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::Reset()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(cross(up, direction));
	glm::vec3 cameraUp = glm::cross(direction, cameraRight);

	viewMatrix = glm::lookAt(position,position+direction,cameraUp);
}
