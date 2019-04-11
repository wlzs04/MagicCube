#include "Camera.h"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../ThreeParty/glm/ext/matrix_clip_space.hpp"

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
	direction = glm::normalize(newDirection);
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

glm::mat4 Camera::GetProjectMatrix()
{
	return glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void Camera::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float Camera::GetSpeed()
{
	return speed;
}

void Camera::SetSensitivity(float newSensitivity)
{
	sensitivity = newSensitivity;
}

float Camera::GetSensitivity()
{
	return sensitivity;
}

void Camera::Rise(float timeValue)
{
	MovePosition(0, timeValue * speed, 0);
}

void Camera::Walk(float timeValue)
{
	float moveLength = timeValue * speed;
	position += direction * moveLength;
	Reset();
}

void Camera::Strafe(float timeValue)
{
	float moveLength = timeValue * speed;
	position -= glm::normalize(glm::cross(direction, cameraUp)) * moveLength;
	Reset();
}

void Camera::Pitch(float timeValue)
{
	float realValue = timeValue * sensitivity;
	pitchAngle += realValue;
	if (pitchAngle > pitchAngleLimit)
	{
		realValue -= pitchAngle - pitchAngleLimit;
		pitchAngle = pitchAngleLimit;
	}
	else if(pitchAngle < -pitchAngleLimit)
	{
		realValue += - pitchAngleLimit - pitchAngle;
		pitchAngle = -pitchAngleLimit;
	}
	glm::mat4 rMatrix= glm::mat4(1);
	rMatrix = glm::rotate(rMatrix, realValue, cameraRight);
	glm::vec4 newDirection = glm::vec4(direction.x, direction.y, direction.z, 0);
	direction = glm::vec3(rMatrix * newDirection);
	Reset();
}

void Camera::RotationY(float timeValue)
{
	float realValue = timeValue * sensitivity;
	glm::mat4 rMatrix = glm::mat4(1);
	rMatrix = glm::rotate(rMatrix, realValue, cameraUp);
	glm::vec4 newDirection = glm::vec4(direction.x, direction.y, direction.z, 0);
	direction = glm::vec3(rMatrix * newDirection);
	Reset();
}

void Camera::Reset()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(cross(up, direction));
	cameraUp = glm::cross(direction, cameraRight);

	viewMatrix = glm::lookAt(position,position+direction,cameraUp);
}
