#pragma once
#include "../../ThreeParty/glm/glm.hpp"

class Camera
{
public:
	//设置位置
	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition();

	//移动位置
	void MovePosition(glm::vec3 movePosition);
	void MovePosition(float x, float y, float z);

	//设置观察方向
	void SetDirection(glm::vec3 newDirection);
	glm::vec3 GetDirection();

	//设置观察目标位置
	void SetTargetPosition(glm::vec3 newTargetPosition);

	//获得观察矩阵
	glm::mat4 GetViewMatrix();

	//获得透视矩阵
	glm::mat4 GetProjectMatrix();

	//上升下降
	void Rise(float value);
	//向前后移动
	void Walk(float value);
	//向左右移动
	void Strafe(float value);
	//视角上下转动
	void Pitch(float value);
	//视角左右转动
	void RotationY(float value);
private:
	void Reset();

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 viewMatrix = glm::mat4(1.0f);

	float speed = 0.1f;
};