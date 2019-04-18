#pragma once
#include "../ProjectBase/ProjectBase.h"

//魔方
class MagicCube:public ProjectBase
{
public:
	MagicCube();
	~MagicCube();
private:
	void InitProject() override;
	void EveryTickCallBack();

	void InputKeyCallBack(int key, int action) override;
	void MouseButtonCallBack(int key,int action) override;
	void MousePositionCallBack(double xPosition, double yPosition) override;

	Material* material = nullptr;
	Actor* actor1 = nullptr;
	Actor* actor2 = nullptr;

	glm::vec2 lastMousePosition = glm::vec2(0);
	bool moveCamera = false;
	float cameraLookRadius = 5;
	float currentCameraAngleH = 0;
	float currentCameraAngleV = 0;
};