#include "Camera.h"

void Camera::SetPosition(vec3 newPosition)
{
	position = newPosition;
}

vec3 Camera::GetPosition()
{
	return position;
}
