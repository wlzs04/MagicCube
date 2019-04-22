#include "MagicChildCubeActor.h"
#include "../../Manager/MeshManager.h"
#include "../../Game/Material/Material.h"
#include "../../Common/CommonHelper.h"

MagicChildCubeActor::MagicChildCubeActor(wstring actorName):Actor(actorName)
{
	wstring materialPath = CommonHelper::GetCurrentPath() + L"/Project/MagicCube/Material/ChildCube.llmat";

	Actor* actorTop = new Actor(actorName + L"PlaneTop");
	Material* materialTop = new Material();
	materialTop->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialTop);
	actorTop->SetMaterial(materialTop);
	actorTop->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorTop->SetPosition(glm::vec3( 0,0.5,0));
	AddChild(actorTop);
	planeList.push_back(actorTop);

	Actor* actorBottom = new Actor(actorName + L"PlaneBottom");
	Material * materialBottom = new Material();
	materialBottom->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialBottom);
	actorBottom->SetMaterial(materialBottom);
	actorBottom->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorBottom->SetPosition(glm::vec3(0, -0.5, 0));
	AddChild(actorBottom);
	planeList.push_back(actorBottom);

	Actor* actorFront = new Actor(actorName + L"PlaneFront");
	Material * materialFront = new Material();
	materialFront->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialFront);
	actorFront->SetMaterial(materialFront);
	actorFront->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorFront->SetPosition(glm::vec3(0, 0, 0.5));
	actorFront->SetRotation(glm::vec3(3.14/2, 0, 0));
	AddChild(actorFront);
	planeList.push_back(actorFront);

	Actor* actorBack = new Actor(actorName + L"PlaneBack");
	Material * materialBack = new Material();
	materialBack->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialBack);
	actorBack->SetMaterial(materialBack);
	actorBack->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorBack->SetPosition(glm::vec3(0, 0, -0.5));
	actorBack->SetRotation(glm::vec3(-3.14 / 2, 0, 0));
	AddChild(actorBack);
	planeList.push_back(actorBack);

	Actor* actorLeft = new Actor(actorName + L"PlaneLeft");
	Material * materialLeft = new Material();
	materialLeft->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialLeft);
	actorLeft->SetMaterial(materialLeft);
	actorLeft->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorLeft->SetPosition(glm::vec3(-0.5, 0, 0));
	actorLeft->SetRotation(glm::vec3(0, 0, 3.14 / 2));
	AddChild(actorLeft);
	planeList.push_back(actorLeft);

	Actor* actorRight = new Actor(actorName + L"PlaneRight");
	Material * materialRight = new Material();
	materialRight->LoadMaterialFromFile(materialPath);
	materialList.push_back(materialRight);
	actorRight->SetMaterial(materialRight);
	actorRight->SetMesh(MeshManager::GetInstance()->CreatePlane());
	actorRight->SetPosition(glm::vec3(0.5, 0, 0));
	actorRight->SetRotation(glm::vec3(0, 0, -3.14 / 2));
	AddChild(actorRight);
	planeList.push_back(actorRight);
}

MagicChildCubeActor::~MagicChildCubeActor()
{
	for (auto var : planeList)
	{
		delete var;
	}
	for (auto var : materialList)
	{
		delete var;
	}
}

void MagicChildCubeActor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	Actor::Render(projectionMatrix, viewMatrix);

	for (auto var : planeList)
	{
		var->Render(projectionMatrix, viewMatrix);
	}
}
