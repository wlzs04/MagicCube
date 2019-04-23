#pragma once
#include <vector>
#include "../../Game/Actor/Actor.h"
#include "MagicChildCubeActor.h"

using namespace std;

class MagicCubeActor :public Actor
{
public:
	MagicCubeActor(wstring actorName);
	~MagicCubeActor();
	
	void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
	vector<MagicChildCubeActor*> childCubeList;
	int totalRow = 3;
	int totalCol = 3;
	int totalDep = 3;

	float cubeActorScale = 0.9f;
};