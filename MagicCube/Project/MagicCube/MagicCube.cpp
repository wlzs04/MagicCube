#include "MagicCube.h"

MagicCube::MagicCube():ProjectBase(L"MagicCube")
{
}

MagicCube::~MagicCube()
{
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}
	if (actor1 != nullptr)
	{
		delete actor1;
		actor1 = nullptr;
	}
	if (actor2 != nullptr)
	{
		delete actor2;
		actor2 = nullptr;
	}
}

void MagicCube::InitProject()
{
	wstring materialPath = GetProjectPath() + L"/Material/Cube.llmat";
	
	material = new Material();
	material->LoadMaterialFromFile(materialPath);

	actor1 = new Actor();
	actor1->SetMesh(MeshManager::GetInstance()->CreateCube());
	actor1->SetMaterial(material);

	actor2 = new Actor();
	actor2->SetMesh(MeshManager::GetInstance()->CreateCube());
	actor2->SetMaterial(material);
	actor2->GetMesh()->SetPosition(glm::vec3(0,0,1.5));
}

void MagicCube::InputKeyCallBack(int key, int action)
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

void MagicCube::MouseButtonCallBack(int key, int action)
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
}

void MagicCube::MousePositionCallBack(double xPosition, double yPosition)
{
	if (moveCamera)
	{
		float rateX = -0.01f;
		float rateY = 0.01f;

		float moveX = (float)xPosition - lastMousePosition.x;
		float moveY = (float)yPosition - lastMousePosition.y;

		float angleYaw = moveX * rateX;
		float anglePitch = moveY * rateY;

		GetCamera()->SetTargetPosition(glm::vec3(0,0,0));

		currentCameraAngleH += angleYaw;
		GetCamera()->SetPosition(glm::vec3(sinf(currentCameraAngleH)*cameraLookRadius,0, cosf(currentCameraAngleH) * cameraLookRadius));
		//GetCamera()->RotationY(angleYaw);
		//GetCamera()->Pitch(anglePitch);
	}
	lastMousePosition = glm::vec2(xPosition, yPosition);
}

void MagicCube::EveryTickCallBack()
{
	float thisTickTime = GetTimeHelper()->GetThisTickTime();
	/*if (GetWindow()->CheckInputKeyPressed('Q'))
	{
		GetCamera()->Rise(-thisTickTime);
	}
	if (GetWindow()->CheckInputKeyPressed('E'))
	{
		GetCamera()->Rise(thisTickTime);
	}
	if (GetWindow()->CheckInputKeyPressed('W'))
	{
		GetCamera()->Walk(thisTickTime);
	}
	if (GetWindow()->CheckInputKeyPressed('S'))
	{
		GetCamera()->Walk(-thisTickTime);
	}
	if (GetWindow()->CheckInputKeyPressed('A'))
	{
		GetCamera()->Strafe(thisTickTime);
	}
	if (GetWindow()->CheckInputKeyPressed('D'))
	{
		GetCamera()->Strafe(-thisTickTime);
	}*/

	actor1->Render(GetCamera()->GetProjectMatrix(), GetCamera()->GetViewMatrix());
	actor2->Render(GetCamera()->GetProjectMatrix(), GetCamera()->GetViewMatrix());
}