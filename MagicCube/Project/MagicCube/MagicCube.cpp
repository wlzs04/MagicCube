#include "MagicCube.h"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../ThreeParty/glm/gtc/type_ptr.hpp"

MagicCube::~MagicCube()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}
	if (actor != nullptr)
	{
		delete actor;
		actor = nullptr;
	}
}

void MagicCube::InitProject()
{
	string materialPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Shader/Cube";
	string vsPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Shader/Cube.vs";
	string fsPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Shader/Cube.fs";

	string imagePath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Texture/me.jpg";
	
	material = new Material();
	material->LoadMaterialFromFile(materialPath);

	texture = new Texture();
	texture->LoadTexture(imagePath);

	actor = new Actor();
	actor->SetMesh(MeshManager::GetInstance()->CreateCube());
	actor->SetMaterial(material);
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

void MagicCube::WindowSizeChangeCallBack(int width, int height)
{
	
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

		GetCamera()->RotationY(angleYaw);
		GetCamera()->Pitch(anglePitch);
	}
	lastMousePosition = glm::vec2(xPosition, yPosition);
}

void MagicCube::EveryTickCallBack()
{
	float thisTickTime = GetTimeHelper().GetThisTickTime();
	if (GetWindow()->CheckInputKeyPressed('Q'))
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
	}

	actor->Render(GetCamera()->GetProjectMatrix(), GetCamera()->GetViewMatrix());

	//shader->Use();

	// 在绑定纹理之前先激活纹理单元
	
	//GetGraphicsApi()->SetTexture(0,texture);

	/*shader->SetMatrix4("projection", GetCamera()->GetProjectMatrix());
	shader->SetMatrix4("view", GetCamera()->GetViewMatrix());
	shader->SetMatrix4("model", mesh->GetWorldMatrix());
	GetGraphicsApi()->DrawSprite(sprite);*/
}