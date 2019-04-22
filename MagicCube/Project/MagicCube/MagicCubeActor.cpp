#include "MagicCubeActor.h"
#include "../../Common/CommonHelper.h"
#include "../../Game/Material/Material.h"
#include "../../Manager/MeshManager.h"
#include "../../Game/Material/MaterialSlot.h"

MagicCubeActor::MagicCubeActor(wstring actorName):Actor(actorName)
{
	int positionOffsetX = 1;
	int positionOffsetY = 1;
	int positionOffsetZ = 1;

	for (int row = 0; row < totalRow; row++)
	{
		for (int col = 0; col < totalCol; col++)
		{
			for (int dep = 0; dep < totalDep; dep++)
			{
				MagicChildCubeActor* actor = new MagicChildCubeActor(actorName + L"cube" +L"_r"+ to_wstring(row) + L"_c" + to_wstring(col) + L"_d" + to_wstring(dep));
				childCubeList.push_back(actor);

				actor->SetPosition(glm::vec3(col - positionOffsetX, row - positionOffsetY, dep - positionOffsetZ));
				actor->SetScale(glm::vec3(cubeActorScale, cubeActorScale, cubeActorScale));
				AddChild(actor);
			}
		}
	}
}

MagicCubeActor::~MagicCubeActor()
{
	for (auto var : childCubeList)
	{
		delete var;
	}
}

void MagicCubeActor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	Actor::Render(projectionMatrix, viewMatrix);

	for (auto var : childCubeList)
	{
		var->Render(projectionMatrix, viewMatrix);
	}
}