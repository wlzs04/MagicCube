#include "Scene.h"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"

Scene::Scene(wstring sceneName)
{
	this->sceneName = sceneName;
}

Scene::~Scene()
{
	for (auto var : cameraList)
	{
		delete var;
	}
	for (auto var : actorMap)
	{
		delete var.second;
	}
}

Camera* Scene::CreateCamera()
{
	Camera* camera = new Camera();
	cameraList.push_back(camera);
	return camera;
}

Actor* Scene::GetPickActorByCameraAndMouse(Camera* camera, glm::vec2 mousePosition)
{
	bool havePick = false;

	glm::uvec4 rayOrigin = glm::uvec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 pm4 = camera->GetProjectMatrix();
	float top = 0, left = 0;
	float vx = ((+2.0f * mousePosition.x) / camera->GetWidth() - 1.0f) / pm4[0][0];
	float vy = ((-2.0f * mousePosition.y) / camera->GetHeight() + 1.0f) / pm4[1][1];
	glm::uvec4 rayDir = glm::uvec4(vx, vy, 1.0f, 0.0f);

	glm::uvec4 newrayOrigin;
	glm::uvec4 newrayDir;
	glm::mat4 vm4 = camera->GetViewMatrix();
	glm::mat4 invView = glm::inverse(vm4);
	rayOrigin = rayOrigin*invView;
	rayDir = rayDir*invView;

	/*{
		if (haveMeshPicked)
		{
			float ttemp = MathHelper::Infinity;
			if (renderObjectManager->coordinateAxes->CheckPick(rayOrigin, rayDir, ttemp))
			{
				return;
			}
		}
	}

	if (!(Util::IsKeyDown(VK_CONTROL)))
	{
		mapIPickObjectPicked.clear();
		currentPickObject = NULL;
		haveMeshPicked = false;
	}

#pragma region 拾取图形和元件
	wstring wstemp;
	float tmin = MathHelper::Infinity;
	for each (auto var in renderObjectManager->mapIRenderObject)
	{
		newrayOrigin = rayOrigin;
		newrayDir = rayDir;

		float ttemp = MathHelper::Infinity;
		if (var.second->CheckPick(newrayOrigin, newrayDir, ttemp))
		{
			havePick = true;

			if (ttemp < tmin)
			{
				wstemp = var.first;
				currentPickObject = var.second;
				tmin = ttemp;
			}
		}
	}
	for each (auto var in mapIComponentObject)
	{
		newrayOrigin = rayOrigin;
		newrayDir = rayDir;

		float ttemp = MathHelper::Infinity;
		if (var.second->CheckPick(newrayOrigin, newrayDir, ttemp))
		{
			havePick = true;

			if (ttemp < tmin)
			{
				wstemp = var.first;
				currentPickObject = var.second;
				tmin = ttemp;
			}
		}
	}
	if (havePick)
	{
		if (mapIPickObjectPicked.count(wstemp) == 0)
		{
			mapIPickObjectPicked[wstemp] = currentPickObject;
		}
		else
		{
			mapIPickObjectPicked.erase(wstemp);
		}
	}
	if (mapIPickObjectPicked.size() > 0)
	{
		haveMeshPicked = true;
		SetCoordinateAxesTransform(currentPickObject);
		XMFLOAT3 temp3;
		switch (renderObjectManager->coordinateAxes->coordinateAxesState)
		{
		case CoordinateAxesState_Position:
		{
			temp3 = currentPickObject->position3;
			break;
		}
		case CoordinateAxesState_Rotate:
		{
			temp3 = currentPickObject->rotate3;
			break;
		}
		case CoordinateAxesState_Scale:
		{
			temp3 = currentPickObject->scale3;
			break;
		}
		}
		uiManager->ShowMeshTransform(temp3.x, temp3.y, temp3.z);
	}
#pragma endregion*/
}

void Scene::RenderSceneToCamera(Camera* camera)
{
	for (auto var : actorMap)
	{
		var.second->Render(camera->GetProjectMatrix(), camera->GetViewMatrix());
	}
}
