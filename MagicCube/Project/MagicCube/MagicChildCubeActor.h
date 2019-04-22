#pragma once
#include <vector>
#include "../../Game/Actor/Actor.h"

class MagicChildCubeActor :public Actor
{
public:
	MagicChildCubeActor(wstring actorName);
	~MagicChildCubeActor();

	void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
	vector<Actor*> planeList;
	vector<Material*> materialList;
};