#include "MagicCubeActor.h"
#include "../../Common/CommonHelper.h"
#include "../../Game/Material/Material.h"
#include "../../Manager/MeshManager.h"

MagicCubeActor::MagicCubeActor(wstring actorName):Actor(actorName)
{
	wstring materialPath = CommonHelper::GetCurrentPath() + L"/Project/MagicCube/Material/Cube.llmat";

	Material* material = new Material();
	material->LoadMaterialFromFile(materialPath);

	int positionOffsetX = 1;
	int positionOffsetY = 1;
	int positionOffsetZ = 1;

	//第一排
	for (int row = 0; row < totalRow; row++)
	{
		for (int col = 0; col < totalCol; col++)
		{
			for (int dep = 0; dep < totalDep; dep++)
			{
				Actor* actor = new Actor(actorName + L"cube" +L"_r"+ to_wstring(row) + L"_c" + to_wstring(col) + L"_d" + to_wstring(dep));
				cubeActorList.push_back(actor);

				actor->SetMesh(MeshManager::GetInstance()->CreateCube());
				actor->SetMaterial(material);
				actor->GetMesh()->SetPosition(glm::vec3(col - positionOffsetX, row - positionOffsetY, dep - positionOffsetZ));
				actor->GetMesh()->SetScale(glm::vec3(cubeActorScale, cubeActorScale, cubeActorScale));
				AddChild(actor);
			}
		}
	}
}

MagicCubeActor::~MagicCubeActor()
{
	for (auto var : cubeActorList)
	{
		delete var;
	}
}

void MagicCubeActor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	Actor::Render(projectionMatrix, viewMatrix);

	for (auto var : cubeActorList)
	{
		var->Render(projectionMatrix, viewMatrix);
	}
}
