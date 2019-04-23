#include "MagicCubeProject.h"
#include "MagicCubeActor.h"

MagicCubeProject::MagicCubeProject():ProjectBase(L"MagicCube")
{
}

MagicCubeProject::~MagicCubeProject()
{
}

void MagicCubeProject::InitProject()
{
	magicCubeActor = SceneManager::GetInstance()->GetCurrentScene()->CreateActor<MagicCubeActor>(L"MagicCube");
	
	GetCamera()->SetPosition(glm::vec3(0,0,cameraLookRadius));
}

void MagicCubeProject::InputKeyCallBack(int key, int action)
{
	//如果是按键传入为大写字母。
	switch (key)
	{
	case GLFW_KEY_ESCAPE://'ESCAPE'
		End();
		break;
	default:
		break;
	}
}

void MagicCubeProject::MouseButtonCallBack(int key, int action)
{
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			moveCamera = true;
		}
		else if(action == GLFW_RELEASE)
		{
			moveCamera = false;
		}
	}
	if (key == GLFW_MOUSE_BUTTON_LEFT)
	{
		SceneManager::GetInstance()->GetCurrentScene()->GetPickActorByCameraAndMouse(GetCamera(), lastMousePosition);
	}
}

void MagicCubeProject::MousePositionCallBack(double xPosition, double yPosition)
{
	if (moveCamera)
	{
		float rateX = -0.004f;
		float rateY = 0.004f;

		float moveX = (float)xPosition - lastMousePosition.x;
		float moveY = (float)yPosition - lastMousePosition.y;

		float angleYaw = moveX * rateX;
		float anglePitch = moveY * rateY;

		currentCameraAngleH += angleYaw;
		currentCameraAngleV += anglePitch;

		currentCameraAngleV = glm::clamp(currentCameraAngleV, -3.14f / 2, 3.14f / 2);

		GetCamera()->SetPosition(glm::vec3(cosf(currentCameraAngleV)*sinf(currentCameraAngleH)*cameraLookRadius, sinf(currentCameraAngleV) * cameraLookRadius, cosf(currentCameraAngleV) * cosf(currentCameraAngleH) * cameraLookRadius));
		GetCamera()->SetTargetPosition(glm::vec3(0, 0, 0));
	}
	lastMousePosition = glm::vec2(xPosition, yPosition);
}

void MagicCubeProject::EveryTickCallBack()
{
}