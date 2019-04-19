#pragma once
#include "../ProjectBase/ProjectBase.h"

//魔方
class MagicCubeProject :public ProjectBase
{
public:
	MagicCubeProject();
	~MagicCubeProject();
private:
	void InitProject() override;
	void EveryTickCallBack();

	void InputKeyCallBack(int key, int action) override;
	void MouseButtonCallBack(int key,int action) override;
	void MousePositionCallBack(double xPosition, double yPosition) override;

	Material* material = nullptr;
	Actor* magicCubeActor = nullptr;

	glm::vec2 lastMousePosition = glm::vec2(0);
	bool moveCamera = false;
	float cameraLookRadius = 6;
	float currentCameraAngleH = 0;
	float currentCameraAngleV = 0;
};