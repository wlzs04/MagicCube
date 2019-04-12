#pragma once
#include "../ProjectBase.h"
#include "../../ThreeParty/glm/glm.hpp"
#include "../../Game/Actor.h"

//魔方
class MagicCube:public ProjectBase
{
public:
	~MagicCube();
private:
	void InitProject() override;
	void EveryTickCallBack();

	void InputKeyCallBack(int key, int action) override;
	void WindowSizeChangeCallBack(int width, int height) override;
	void MouseButtonCallBack(int key,int action) override;
	void MousePositionCallBack(double xPosition, double yPosition) override;

	Material* material = nullptr;
	Texture* texture = nullptr;
	Actor* actor = nullptr;

	glm::vec2 lastMousePosition = glm::vec2(0);
	bool moveCamera = false;
};